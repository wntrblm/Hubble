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

/* Static variables */

/* Forward declarations */

int main(void);
static void init();
static void loop();

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
    /* Configure clocks. */
    stel_clocks_init();
    wntr_ticks_init();

    /* Setup USB as soon as possible */
    stel_usb_init();

    /* Configure peripherals */
    stel_dotstar_init(64);

    stel_dac_init();
    stel_dac_init_output(A5);
    stel_dac_init_output(A14);

    stel_adc_init();
    stel_adc_init_input(A1);
    stel_adc_init_input(A2);
    stel_adc_init_input(A3);
    stel_adc_init_input(A4);
    stel_adc_init_input(A6);
    stel_adc_init_input(A7);
    stel_adc_init_input(A8);
    stel_adc_init_input(A9);
    stel_adc_init_input(A10);
    stel_adc_init_input(A11);
    stel_adc_init_input(A12);
    stel_adc_init_input(A13);
    stel_adc_init_input(A15);
    stel_adc_init_input(A16);
    stel_adc_init_input(A17);
    stel_adc_init_input(A18);
    stel_adc_init_input(A19);
    stel_adc_init_input(A20);

    stel_ad5685_init();
    stel_ad5685_soft_reset();
}

/* Private functions */

static void loop() {
    /* Dotstar update */
    static uint16_t hue = 0;
    stel_dotstar_set32(0, wntr_colorspace_hsv_to_rgb(hue, 200, 255));
    stel_dotstar_update();
    hue += 5;

    /* MIDI I/O update */
    // struct WntrMIDIMessage midi_msg = {};

    // if (wntr_midi_receive(&midi_msg)) {
    //     in.midi_msg = &midi_msg;
    // } else {
    //     in.midi_msg = NULL;
    // }

    /* ADC update */
    const uint16_t a1 = stel_adc_read_sync(A1);
    const uint16_t a2 = stel_adc_read_sync(A2);
    const uint16_t a3 = stel_adc_read_sync(A3);
    const uint16_t a4 = stel_adc_read_sync(A4);
    const uint16_t a6 = stel_adc_read_sync(A6);
    const uint16_t a7 = stel_adc_read_sync(A7);
    const uint16_t a8 = stel_adc_read_sync(A8);
    const uint16_t a9 = stel_adc_read_sync(A9);
    const uint16_t a10 = stel_adc_read_sync(A10);
    const uint16_t a11 = stel_adc_read_sync(A11);
    const uint16_t a12 = stel_adc_read_sync(A12);
    const uint16_t a13 = stel_adc_read_sync(A13);
    const uint16_t a15 = stel_adc_read_sync(A15);
    const uint16_t a16 = stel_adc_read_sync(A16);
    const uint16_t a17 = stel_adc_read_sync(A17);
    const uint16_t a18 = stel_adc_read_sync(A18);
    const uint16_t a19 = stel_adc_read_sync(A19);
    const uint16_t a20 = stel_adc_read_sync(A20);

    printf(
        "ADC: %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u %04u\n",
        a1,
        a2,
        a3,
        a4,
        a6,
        a7,
        a8,
        a9,
        a10,
        a11,
        a12,
        a13,
        a15,
        a16,
        a17,
        a18,
        a19,
        a20);

    /* Update DAC outputs. */

    stel_dac_set(A5, a1);
    stel_dac_set(A14, a2);

    stel_ad5685_write_channel(AD5685_CHANNEL_A, a17 << 4, true);
    stel_ad5685_write_channel(AD5685_CHANNEL_B, a18 << 4, true);
    stel_ad5685_write_channel(AD5685_CHANNEL_C, a19 << 4, true);
    stel_ad5685_write_channel(AD5685_CHANNEL_D, a20 << 4, true);
}
