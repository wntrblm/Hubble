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
#include "wntr_data_converter_helpers.h"
#include "wntr_delay.h"
#include "wntr_gpio.h"
#include "wntr_sysex_utils.h"
#include "wntr_ticks.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Macros */

/* Global state */

static bool calibration_enabled = true;

static const struct WntrVoltageCalibrationTableEntry dac_reference_calibration_entires_[] = {
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

#define DEF_CALIBRATION_TABLE(name)                                                                                    \
    static struct WntrVoltageCalibrationTableEntry                                                                     \
        name##_calibration_table_entries_[WNTR_ARRAY_LEN(dac_reference_calibration_entires_)];                         \
    static struct WntrVoltageCalibrationTable name##_calibration_table = {                                             \
        .entries = name##_calibration_table_entries_,                                                                  \
        .len = WNTR_ARRAY_LEN(name##_calibration_table_entries_),                                                      \
    };

DEF_CALIBRATION_TABLE(dac_1);
DEF_CALIBRATION_TABLE(dac_2);
DEF_CALIBRATION_TABLE(dac_3);
DEF_CALIBRATION_TABLE(dac_4);
DEF_CALIBRATION_TABLE(adc_1);
DEF_CALIBRATION_TABLE(adc_2);
DEF_CALIBRATION_TABLE(adc_3);
DEF_CALIBRATION_TABLE(adc_4);

static struct WntrVoltageCalibrationTable* calibration_tables[] = {
    &dac_1_calibration_table,
    &dac_2_calibration_table,
    &dac_3_calibration_table,
    &dac_4_calibration_table,
    &adc_1_calibration_table,
    &adc_2_calibration_table,
    &adc_3_calibration_table,
    &adc_4_calibration_table,
};

/* Forward declarations */

int main(void);
static void init();
static void init_calibrations();
static void init_dacs();
static void loop();
static void register_sysex_commands();

WNTR_SYSEX_COMMAND_DECL(0x01, hello);
WNTR_SYSEX_COMMAND_DECL(0x02, reset);
WNTR_SYSEX_COMMAND_DECL(0x03, read_gpio);
WNTR_SYSEX_COMMAND_DECL(0x04, set_gpio);
WNTR_SYSEX_COMMAND_DECL(0x05, read_adc);
WNTR_SYSEX_COMMAND_DECL(0x06, read_adc_voltage);
WNTR_SYSEX_COMMAND_DECL(0x07, set_dac);
WNTR_SYSEX_COMMAND_DECL(0x08, set_dac_voltage);
WNTR_SYSEX_COMMAND_DECL(0x50, set_calibration_enabled);
WNTR_SYSEX_COMMAND_DECL(0x51, set_calibration_table_entry);
WNTR_SYSEX_COMMAND_DECL(0x52, save_calibration_table);

/* Public functions */

int main(void) {
    init();
    printf("Hello, I'm Hubble!\n");

    while (1) {
        wntr_usb_task();
        loop();
    }

    return 0;
}

/* Private functions */

static void init() {
    SystemInit();

    /* Turn on the "alive" LED */
    WntrGPIOPin_set_as_output(PIN_STATUS_LED);
    WntrGPIOPin_set(PIN_STATUS_LED, true);

    /* Setup USB as soon as possible */
    wntr_usb_init();

    /* Configure peripherals */
    hubble_dotstar_init(20);

    hubble_adc_init();
    // hubble_adc_init_input(&ADC_A1);

    /* SPI bus & external DAC */
    WntrSERCOMSPI_init(&AD5685_SPI);
    hubble_ad5685_init(&AD5685_SPI);
    hubble_ad5685_soft_reset();

    /* Calibrations */
    init_calibrations();

    /* Set initial values for dacs and muxes */
    init_dacs();

    /* Sysex commands */
    register_sysex_commands();
}

static void init_calibrations() {
    for (size_t i = 0; i < WNTR_ARRAY_LEN(calibration_tables); i++) {
        struct WntrVoltageCalibrationTable table = *calibration_tables[i];
        /* Initialize the table with the reference calibration. */
        memcpy(
            table.entries,
            dac_reference_calibration_entires_,
            sizeof(struct WntrVoltageCalibrationTableEntry) * table.len);
        /* Load the saved values (if available) */
        HubbleVoltageCalibrationTable_load_from_nvm(table, i);
    }
}

static void init_dacs() {
    // Yes, slightly above zero, since MCU inputs tend to be
    // more forgiving of a very small positive voltage than any negative
    // voltage.
    uint32_t zero_code_point = wntr_volts_to_code_points(0.1f, WNTR_RESOLUTION_16_BIT, -8.0f, 8.0f, true);
    hubble_ad5685_write_channel(0, zero_code_point, true);
    hubble_ad5685_write_channel(1, zero_code_point, true);
    hubble_ad5685_write_channel(2, zero_code_point, true);
    hubble_ad5685_write_channel(3, zero_code_point, true);
}

static void loop() {
    /* Blink the LED */
    if ((wntr_ticks() / 100) % 2 == 0) {
        WntrGPIOPin_set(PIN_STATUS_LED, true);
    } else {
        WntrGPIOPin_set(PIN_STATUS_LED, false);
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
    WNTR_REGISTER_SYSEX_COMMAND(0x01, hello);
    WNTR_REGISTER_SYSEX_COMMAND(0x02, reset);
    WNTR_REGISTER_SYSEX_COMMAND(0x03, read_gpio);
    WNTR_REGISTER_SYSEX_COMMAND(0x04, set_gpio);
    WNTR_REGISTER_SYSEX_COMMAND(0x05, read_adc);
    WNTR_REGISTER_SYSEX_COMMAND(0x06, read_adc_voltage);
    WNTR_REGISTER_SYSEX_COMMAND(0x07, set_dac);
    WNTR_REGISTER_SYSEX_COMMAND(0x08, set_dac_voltage);
    WNTR_REGISTER_SYSEX_COMMAND(0x50, set_calibration_enabled);
    WNTR_REGISTER_SYSEX_COMMAND(0x51, set_calibration_table_entry);
    WNTR_REGISTER_SYSEX_COMMAND(0x52, save_calibration_table);
}

WNTR_SYSEX_COMMAND_DECL(0x01, hello) {
    /*
        Response: 0x01 and the build info string, for example:
        "12.24.2020 on 20/01/2021 23:38 UTC with arm-none-eabi-gcc 10.2.1 20201103 (release) by
        stargirl@stargirls-mbp.lan"
    */

    const char* build_info = wntr_build_info_string();
    size_t build_info_len = strlen(build_info);

    WNTR_SYSEX_PREPARE_RESPONSE(0x01, 128);

    /* Don't copy more of the build info string than we have room for. */
    if (build_info_len > response_len) {
        build_info_len = response_len;
    }

    memccpy(response, build_info, 0, 128);

    WNTR_SYSEX_SEND_RESPONSE();

    printf("SysEx 0x01: Hello! Build info length: %u\n", build_info_len);
}

WNTR_SYSEX_COMMAND_DECL(0x02, reset) {
    /* Response: None */
    printf("SysEx 0x02: Reset requested\n");
    NVIC_SystemReset();
}

WNTR_SYSEX_COMMAND_DECL(0x03, read_gpio) {
    /* Request: GPIO Pin (1) */
    /* Response: Value (1) */

    uint8_t pin = request_data[0];

    WntrGPIOPin_set_as_input(GPIO[pin], false);

    uint8_t result = WntrGPIOPin_get(GPIO[pin]);

    WNTR_SYSEX_RESPONSE_UNARY(0x03, result);

    printf("SysEx 0x03: Read GPIO %u, result %u\n", pin, result);
}

WNTR_SYSEX_COMMAND_DECL(0x04, set_gpio) {
    /* Request: GPIO Pin (1), value (1) */
    /* Response: ACK */

    uint8_t pin = request_data[0];
    uint8_t value = request_data[1];

    WntrGPIOPin_set_as_output(GPIO[pin]);
    WntrGPIOPin_set(GPIO[pin], value ? true : false);

    WNTR_SYSEX_RESPONSE_NULLARY(0x04);

    printf("SysEx 0x04: Set GPIO %u to %u\n", pin, value);
}

WNTR_SYSEX_COMMAND_DECL(0x05, read_adc) {
    /* Request: CHANNEL(1) MUX(1) */
    /* Response (teeth): VALUE(2) */

    uint8_t channel = request_data[0];
    uint8_t mux = request_data[1];

    // TODO
    // uint16_t result = hubble_adc_read_sync(&ADC_CHANNELS[channel]);
    uint16_t result = 0;

    WNTR_SYSEX_PREPARE_RESPONSE(0x05, TEETH_ENCODED_LENGTH(2));

    uint8_t unencoded_response[2];
    WNTR_PACK_16(result, unencoded_response, 0);
    teeth_encode(unencoded_response, 2, response);

    WNTR_SYSEX_SEND_RESPONSE();

    printf("SysEx 0x05: Read ADC %u:%u, result %u\n", mux, channel, result);
}

WNTR_SYSEX_COMMAND_DECL(0x06, read_adc_voltage) {
    /* Request: CHANNEL(1) MUX(1) */
    /* Response (teeth): VALUE(4) */
    uint8_t channel = request_data[0];
    uint8_t mux = request_data[1];

    // TODO
    // uint16_t code_points = hubble_adc_read_sync(&ADC_CHANNELS[channel]);
    uint16_t code_points = 0;

    float result = wntr_code_points_to_volts(code_points, WNTR_RESOLUTION_12_BIT, -8.0f, 8.0f, true);

    if (calibration_enabled) {
        result = WntrVoltageCalibrationTable_lookup(result, *calibration_tables[4 + channel]);
    } else {
        printf("Warning: calibration tables disabled.\n");
    }

    WNTR_SYSEX_PREPARE_RESPONSE(0x06, TEETH_ENCODED_LENGTH(4));

    uint8_t unencoded_response[4];
    WNTR_PACK_FLOAT(result, unencoded_response, 0);
    teeth_encode(unencoded_response, 4, response);

    WNTR_SYSEX_SEND_RESPONSE();

    printf("SysEx 0x06: Read ADC voltage %u:%u is %0.3f\n", mux, channel, (double)(result));
}

WNTR_SYSEX_COMMAND_DECL(0x07, set_dac) {
    /* Request (teeth): CHANNEL(1) MUX(1) VALUE(2) */
    /* Response: ACK */

    WNTR_SYSEX_DECODE_TEETH_REQUEST(4);

    uint8_t channel = request[0];
    uint8_t mux = request[1];
    uint16_t value = WNTR_UNPACK_16(request, 2);

    hubble_ad5685_write_channel(channel, value, true);

    WNTR_SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x07: Set DAC %u:%u to %u\n", mux, channel, value);
}

WNTR_SYSEX_COMMAND_DECL(0x08, set_dac_voltage) {
    /* Request (teeth): CHANNEL(1) MUX(1) VALUE(4) */
    /* Response: ACK */

    WNTR_SYSEX_DECODE_TEETH_REQUEST(6);

    uint8_t channel = request[0];
    uint8_t mux = request[1];
    float value = WNTR_UNPACK_FLOAT(request, 2);

    if (calibration_enabled) {
        value = WntrVoltageCalibrationTable_lookup(value, *calibration_tables[channel]);
    } else {
        printf("Warning: calibration tables disabled.\n");
    }

    uint32_t code_point = wntr_volts_to_code_points(value, WNTR_RESOLUTION_16_BIT, -8.0f, 8.0f, true);

    hubble_ad5685_write_channel(channel, code_point, true);

    WNTR_SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x08: Set DAC voltage %u:%u to %0.3f\n", mux, channel, (double)(value));
}

WNTR_SYSEX_COMMAND_DECL(0x50, set_calibration_enabled) {
    /* Request: ENABLED(1) */
    /* Response: ACK */

    calibration_enabled = request_data[0] ? true : false;

    WNTR_SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x50: Set calibration enabled to: %u\n", calibration_enabled);
}

WNTR_SYSEX_COMMAND_DECL(0x51, set_calibration_table_entry) {
    /* Request (teeth): TABLE(1) INDEX(1) EXPECTED(4), MEASURED(4) */
    /* Response: ACK */

    WNTR_SYSEX_DECODE_TEETH_REQUEST(10);

    uint8_t table = request[0];
    uint8_t index = request[1];
    float expected = WNTR_UNPACK_FLOAT(request, 2);
    float measured = WNTR_UNPACK_FLOAT(request, 6);

    calibration_tables[table]->entries[index].expected = expected;
    calibration_tables[table]->entries[index].measured = measured;

    WNTR_SYSEX_RESPONSE_NULLARY();

    printf(
        "SysEx 0x51: Set calibration table %u[%u] to expected=%0.3f, measured=%0.3f\n",
        table,
        index,
        (double)expected,
        (double)measured);
}

WNTR_SYSEX_COMMAND_DECL(0x52, save_calibration_table) {
    /* Request: TABLE(1) */
    /* Response: ACK */

    uint8_t table = request_data[0];

    HubbleVoltageCalibrationTable_save_to_nvm(*(calibration_tables[table]), table);

    WNTR_SYSEX_RESPONSE_NULLARY();

    printf("SysEx 0x52: Save calibration table %u\n", table);
    WntrVoltageCalibrationTable_print(*(calibration_tables[table]));
}
