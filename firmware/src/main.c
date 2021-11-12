/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "printf.h"
#include "sam.h"
#include "stel.h"
#include "wntr_colorspace.h"
#include "wntr_delay.h"
#include "wntr_gpio.h"
#include "wntr_ticks.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Macros */

#define ADC_12_BIT_TO_FLOAT(val) (u12_invert(map_rangef(val, 0.0f, 4096.0f, -5.0f, 5.0f)))
#define FLOAT_TO_16_BIT_DAC(val) (u16_invert(float_to_u16(map_rangef(val, -5.f, 8.f, 0.f, 1.0f))))
#define FLOAT_TO_12_BIT_DAC(val) (u12_invert(float_to_u12(map_rangef(val, -5.f, 5.f, 0.f, 1.0f))))

/* Forward declarations */

int main(void);
static void init();
static void loop();
static void loop_test_adc();
static void loop_test_dac();
static void loop_test_gpio();

/* Public functions */

int main(void) {
    init();
    printf("Hello, I'm Stellar!\n");

    while (1) {
        stel_usb_task();
        loop();
    }

    return 0;
}

static void init() {
    SystemInit();

    /* Turn on the "alive" LED */
    WntrGPIOPin_set_as_output(GPIO_23_LED);
    WntrGPIOPin_set(GPIO_23_LED, true);

    /* Setup USB as soon as possible */
    stel_usb_init();

    /* Configure peripherals */
    stel_dotstar_init(20);

    stel_adc_init();
    stel_adc_init_input(&ADC_A1);
    stel_adc_init_input(&ADC_A2);
    stel_adc_init_input(&ADC_A3);
    stel_adc_init_input(&ADC_A4);

    /* SPI bus & external DAC */
    stel_sercom_spi_init(&SPI);
    stel_ad5685_init(&SPI);
    stel_ad5685_soft_reset();

    /* Multiplexer address lines */
    WntrGPIOPin_set_as_output(GPIO_DAC_MUX_A0);
    WntrGPIOPin_set_as_output(GPIO_DAC_MUX_A1);
    WntrGPIOPin_set_as_output(GPIO_ADC_MUX_A0);
    WntrGPIOPin_set_as_output(GPIO_ADC_MUX_A1);

    WntrGPIOPin_set(GPIO_DAC_MUX_A0, false);
    WntrGPIOPin_set(GPIO_DAC_MUX_A1, false);
    WntrGPIOPin_set(GPIO_ADC_MUX_A0, false);
    WntrGPIOPin_set(GPIO_ADC_MUX_A1, false);
}

/* Private functions */

static void loop() {
    /* Blink the LED */
    if ((wntr_ticks() / 100) % 2 == 0) {
        WntrGPIOPin_set(GPIO_23_LED, true);
    } else {
        WntrGPIOPin_set(GPIO_23_LED, false);
    }

    /* Dotstar update */
    static uint16_t hue = 0;
    stel_dotstar_set32(0, wntr_colorspace_hsv_to_rgb(hue, 200, 255));
    stel_dotstar_update();
    hue += 10;

    /* MIDI I/O update */
    // struct WntrMIDIMessage midi_msg = {};

    // if (wntr_midi_receive(&midi_msg)) {
    //     in.midi_msg = &midi_msg;
    // } else {
    //     in.midi_msg = NULL;
    // }

    loop_test_adc();
    loop_test_dac();
    loop_test_gpio();
}

static void loop_test_adc() {
    for (uint8_t mux_addr = 0; mux_addr < 4; mux_addr++) {
        WntrGPIOPin_set(GPIO_ADC_MUX_A0, (mux_addr & 0x1));
        WntrGPIOPin_set(GPIO_ADC_MUX_A1, (mux_addr & 0x2) >> 1);

        wntr_delay_ms(5);

        const uint16_t a1 = stel_adc_read_sync(&ADC_A1);
        const uint16_t a2 = stel_adc_read_sync(&ADC_A2);
        const uint16_t a3 = stel_adc_read_sync(&ADC_A3);
        const uint16_t a4 = stel_adc_read_sync(&ADC_A4);

        printf("ADC %u: %04u %04u %04u %04u    ", mux_addr, a1, a2, a3, a4);
    }
    printf("\n");
}

static void loop_test_dac() {
    static uint8_t mux_addr = 0;
    static uint32_t last_update = 0;

    uint32_t now = wntr_ticks();
    if (last_update + 500 < now) {
        mux_addr = (mux_addr + 1) % 4;
    }

    // WntrGPIOPin_set(GPIO_DAC_MUX_A0, (mux_addr & 0x1));
    // WntrGPIOPin_set(GPIO_DAC_MUX_A1, (mux_addr & 0x2) >> 1);

    stel_ad5685_write_channel(AD5685_CHANNEL_A, (wntr_ticks() * 100) % 65355, true);
    stel_ad5685_write_channel(AD5685_CHANNEL_B, 65535 - ((wntr_ticks() * 100) % 65355), true);
    stel_ad5685_write_channel(AD5685_CHANNEL_C, 65535 - ((wntr_ticks() * 10) % 65355), true);
    stel_ad5685_write_channel(AD5685_CHANNEL_D, (wntr_ticks() * 10) % 65355, true);
}

/*
    Steps through each GPIO pin and turns it on and off
*/
static void loop_test_gpio() {
    static size_t gpio_idx = 0;
    static uint32_t last_update = 0;

    uint32_t now = wntr_ticks();
    if (last_update + 100 < now) {
        last_update = now;
        WntrGPIOPin_set(GPIO[gpio_idx], false);

        gpio_idx = (gpio_idx + 1) % 23;
        WntrGPIOPin_set_as_output(GPIO[gpio_idx]);
        WntrGPIOPin_set(GPIO[gpio_idx], true);
    }
}
