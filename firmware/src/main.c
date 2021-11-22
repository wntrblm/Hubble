/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "hubble.h"
#include "printf.h"
#include "wntr_array.h"
#include "wntr_build_info.h"
#include "wntr_colorspace.h"
#include "wntr_delay.h"
#include "wntr_gpio.h"
#include "wntr_ticks.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Macros */

/* Global state */

static bool calibration_enabled = true;

static struct HubbleVoltageCalibrationTableEntry dac_calibration_table_entries_[] = {
    {.expected = -8.0, .measured = -8.0},
    {.expected = -7.0, .measured = -7.0},
    {.expected = -6.0, .measured = -6.0},
    {.expected = -5.0, .measured = -5.0},
    {.expected = -4.0, .measured = -4.0},
    {.expected = -3.0, .measured = -3.0},
    {.expected = -2.0, .measured = -2.0},
    {.expected = -1.0, .measured = -1.0},
    {.expected = 0.0, .measured = -0.0},
    {.expected = 1.0, .measured = 1.0},
    {.expected = 2.0, .measured = 2.0},
    {.expected = 3.0, .measured = 3.0},
    {.expected = 4.0, .measured = 4.0},
    {.expected = 5.0, .measured = 5.0},
    {.expected = 6.0, .measured = 6.0},
    {.expected = 7.0, .measured = 7.0},
    {.expected = 8.0, .measured = 8.0},
};
static struct HubbleVoltageCalibrationTable dac_calibration_table = {
    .entries = dac_calibration_table_entries_,
    .len = WNTR_ARRAY_LEN(dac_calibration_table_entries_),
};

static struct HubbleVoltageCalibrationTableEntry adc_calibration_table_entries_[] = {
    {.expected = -8.0, .measured = -8.0},
    {.expected = -4.0, .measured = -4.0},
    {.expected = 0.0, .measured = -0.0},
    {.expected = 4.0, .measured = 4.0},
    {.expected = 8.0, .measured = 8.0},
};
static struct HubbleVoltageCalibrationTable adc_calibration_table = {
    .entries = adc_calibration_table_entries_,
    .len = WNTR_ARRAY_LEN(adc_calibration_table_entries_),
};

/* Forward declarations */

int main(void);
static void init();
static void loop();

static void register_sysex_commands();
SYSEX_COMMAND_DECL(0x01, hello);
SYSEX_COMMAND_DECL(0x02, reset);
SYSEX_COMMAND_DECL(0x03, read_gpio);
SYSEX_COMMAND_DECL(0x04, set_gpio);
SYSEX_COMMAND_DECL(0x05, read_adc);
SYSEX_COMMAND_DECL(0x06, read_adc_voltage);
SYSEX_COMMAND_DECL(0x07, set_dac);
SYSEX_COMMAND_DECL(0x08, set_dac_voltage);
SYSEX_COMMAND_DECL(0x50, set_calibration_enabled);
SYSEX_COMMAND_DECL(0x51, set_calibration_table_entry);
SYSEX_COMMAND_DECL(0x52, save_calibration_table);

/* Public functions */

int main(void) {
    init();
    printf("Hello, I'm Hubble!\n");

    while (1) {
        hubble_usb_task();
        loop();
    }

    return 0;
}

/* Private functions */

static void init() {
    SystemInit();

    /* Turn on the "alive" LED */
    WntrGPIOPin_set_as_output(GPIO_23_LED);
    WntrGPIOPin_set(GPIO_23_LED, true);

    /* Setup USB as soon as possible */
    hubble_usb_init();

    /* Configure peripherals */
    hubble_dotstar_init(20);

    hubble_adc_init();
    hubble_adc_init_input(&ADC_A1);
    hubble_adc_init_input(&ADC_A2);
    hubble_adc_init_input(&ADC_A3);
    hubble_adc_init_input(&ADC_A4);

    /* SPI bus & external DAC */
    hubble_sercom_spi_init(&SPI);
    hubble_ad5685_init(&SPI);
    hubble_ad5685_soft_reset();

    /* Multiplexers */
    hubble_mux50x_init(DAC_MUX);
    hubble_mux50x_init(ADC_MUX);

    /* Calibrations */
    HubbleVoltageCalibrationTable_load_from_nvm(dac_calibration_table, 0);
    HubbleVoltageCalibrationTable_print(dac_calibration_table);
    HubbleVoltageCalibrationTable_load_from_nvm(adc_calibration_table, 1);
    HubbleVoltageCalibrationTable_print(adc_calibration_table);

    /* Sysex commands */
    register_sysex_commands();
}

static void loop() {
    /* Blink the LED */
    if ((wntr_ticks() / 100) % 2 == 0) {
        WntrGPIOPin_set(GPIO_23_LED, true);
    } else {
        WntrGPIOPin_set(GPIO_23_LED, false);
    }

    /* Dotstar update */
    static uint16_t hue = 0;
    hubble_dotstar_set32(0, wntr_colorspace_hsv_to_rgb(hue, 200, 255));
    hubble_dotstar_update();
    hue += 10;

    /* MIDI I/O update */
    struct WntrMIDIMessage midi_msg = {};

    if (wntr_midi_receive(&midi_msg)) {
        if (midi_msg.code_index == MIDI_CODE_INDEX_SYSEX_START_OR_CONTINUE) {
            wntr_midi_dispatch_sysex();
        }
    }
}

static void register_sysex_commands() {
    REGISTER_SYSEX_COMMAND(0x01, hello);
    REGISTER_SYSEX_COMMAND(0x02, reset);
    REGISTER_SYSEX_COMMAND(0x03, read_gpio);
    REGISTER_SYSEX_COMMAND(0x04, set_gpio);
    REGISTER_SYSEX_COMMAND(0x05, read_adc);
    REGISTER_SYSEX_COMMAND(0x06, read_adc_voltage);
    REGISTER_SYSEX_COMMAND(0x07, set_dac);
    REGISTER_SYSEX_COMMAND(0x08, set_dac_voltage);
    REGISTER_SYSEX_COMMAND(0x50, set_calibration_enabled);
    REGISTER_SYSEX_COMMAND(0x51, set_calibration_table_entry);
    REGISTER_SYSEX_COMMAND(0x52, save_calibration_table);
}

SYSEX_COMMAND_DECL(0x01, hello) {
    /*
        Response: 0x01 and the build info string, for example:
        "12.24.2020 on 20/01/2021 23:38 UTC with arm-none-eabi-gcc 10.2.1 20201103 (release) by
        stargirl@stargirls-mbp.lan"
    */

    const char* build_info = wntr_build_info_string();
    size_t build_info_len = strlen(build_info);

    SYSEX_PREPARE_RESPONSE(0x01, 128);

    /* Don't copy more of the build info string than we have room for. */
    if (build_info_len > response_len) {
        build_info_len = response_len;
    }

    memccpy(response, build_info, 0, 128);

    SYSEX_SEND_RESPONSE();

    printf("SysEx 0x01: Hello! Build info length: %u\n", build_info_len);
}

SYSEX_COMMAND_DECL(0x02, reset) {
    /* Response: None */
    printf("SysEx 0x02: Reset requested\n");
    NVIC_SystemReset();
}

SYSEX_COMMAND_DECL(0x03, read_gpio) {
    /* Request: GPIO Pin (1) */
    /* Response: Value (1) */

    uint8_t pin = request_data[0];

    WntrGPIOPin_set_as_input(GPIO[pin], false);

    uint8_t result = WntrGPIOPin_get(GPIO[pin]);

    SYSEX_RESPONSE_UNARY(0x03, result);

    printf("SysEx 0x03: Read GPIO %u, result %u\n", pin, result);
}

SYSEX_COMMAND_DECL(0x04, set_gpio) {
    /* Request: GPIO Pin (1), value (1) */
    /* Response: ACK */

    uint8_t pin = request_data[0];
    uint8_t value = request_data[1];

    WntrGPIOPin_set_as_output(GPIO[pin]);
    WntrGPIOPin_set(GPIO[pin], value ? true : false);

    SYSEX_RESPONSE_NULLARY(0x04);

    printf("SysEx 0x04: Set GPIO %u to %u\n", pin, value);
}

SYSEX_COMMAND_DECL(0x05, read_adc) {
    /* Request: CHANNEL(1) MUX(1) */
    /* Response (teeth): VALUE(2) */

    uint8_t channel = request_data[0];
    uint8_t mux = request_data[1];

    hubble_mux50x_set(ADC_MUX, mux);
    uint16_t result = hubble_adc_read_sync(&ADC_CHANNELS[channel]);

    SYSEX_PREPARE_RESPONSE(0x05, TEETH_ENCODED_LENGTH(2));

    uint8_t unencoded_response[2];
    WNTR_PACK_16(result, unencoded_response, 0);
    teeth_encode(unencoded_response, 2, response);

    SYSEX_SEND_RESPONSE();

    printf("SysEx 0x05: Read ADC %u:%u, result %u\n", mux, channel, result);
}

SYSEX_COMMAND_DECL(0x06, read_adc_voltage) {}

SYSEX_COMMAND_DECL(0x07, set_dac) {
    /* Request (teeth): CHANNEL(1) MUX(1) VALUE(2) */
    /* Response: ACK */

    SYSEX_DECODE_TEETH_REQUEST(4);

    uint8_t channel = request[0];
    uint8_t mux = request[1];
    uint16_t value = WNTR_UNPACK_16(request, 2);

    hubble_mux50x_set(DAC_MUX, mux);
    hubble_ad5685_write_channel(channel, value, true);

    SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x07: Set DAC %u:%u to %u\n", mux, channel, value);
}

SYSEX_COMMAND_DECL(0x08, set_dac_voltage) {
    /* Request (teeth): CHANNEL(1) MUX(1) VALUE(4) */
    /* Response: ACK */

    SYSEX_DECODE_TEETH_REQUEST(6);

    uint8_t channel = request[0];
    uint8_t mux = request[1];
    float value = WNTR_UNPACK_FLOAT(request, 2);

    if (calibration_enabled) {
        value = HubbleVoltageCalibrationTable_lookup(value, dac_calibration_table);
    }

    uint32_t code_point = hubble_volts_to_code_points(value, HUBBLE_RESOLUTION_16_BIT, -8.0f, 8.0f, true);

    hubble_mux50x_set(DAC_MUX, mux);
    hubble_ad5685_write_channel(channel, code_point, true);

    SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x08: Set DAC voltage %u:%u to %0.3f\n", mux, channel, (double)(value));
}

static struct HubbleVoltageCalibrationTable* calibration_tables_[] = {
    &dac_calibration_table,
    &adc_calibration_table,
};

SYSEX_COMMAND_DECL(0x50, set_calibration_enabled) {
    /* Request: ENABLED(1) */
    /* Response: ACK */

    calibration_enabled = request_data[0] ? true : false;

    SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x50: Set calibration enabled to: %u\n", calibration_enabled);
}

SYSEX_COMMAND_DECL(0x51, set_calibration_table_entry) {
    /* Request (teeth): TABLE(1) INDEX(1) EXPECTED(4), MEASURED(4) */
    /* Response: ACK */

    SYSEX_DECODE_TEETH_REQUEST(10);

    uint8_t table = request[0];
    uint8_t index = request[1];
    float expected = WNTR_UNPACK_FLOAT(request, 2);
    float measured = WNTR_UNPACK_FLOAT(request, 6);

    calibration_tables_[table]->entries[index].expected = expected;
    calibration_tables_[table]->entries[index].measured = measured;

    SYSEX_RESPONSE_NULLARY();

    printf(
        "SysEx 0x51: Set calibration table %u[%u] to expected=%0.3f, measured=%0.3f\n",
        table,
        index,
        (double)expected,
        (double)measured);
}

SYSEX_COMMAND_DECL(0x52, save_calibration_table) {
    /* Request: TABLE(1) */
    /* Response: ACK */

    uint8_t table = request_data[0];

    HubbleVoltageCalibrationTable_save_to_nvm(*(calibration_tables_[table]), table);

    SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x52: Save calibration table %u\n", table);
    HubbleVoltageCalibrationTable_print(*(calibration_tables_[table]));
}
