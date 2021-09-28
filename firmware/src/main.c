/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "flow_runner.h"
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

#define OUTPUT_1_CHANNEL AD5685_CHANNEL_D
#define OUTPUT_2_CHANNEL AD5685_CHANNEL_A
#define OUTPUT_3_CHANNEL AD5685_CHANNEL_B
#define OUTPUT_4_CHANNEL AD5685_CHANNEL_B
#define OUTPUT_DELTA_CHANNEL DAC_CHANNEL_B
#define OUTPUT_GAMMA_CHANNEL DAC_CHANNEL_A

#define ADC_12_BIT_TO_FLOAT(val) (u12_invert(map_rangef(val, 0.0f, 4096.0f, -5.0f, 5.0f)))
#define FLOAT_TO_16_BIT_DAC(val) (u16_invert(float_to_u16(map_rangef(val, -5.f, 8.f, 0.f, 1.0f))))
#define FLOAT_TO_12_BIT_DAC(val) (u12_invert(float_to_u12(map_rangef(val, -5.f, 5.f, 0.f, 1.0f))))

/* Static variables */

static struct StelADCInput input_a = {
    .adc = ADC0,
    .port = WNTR_PORT_B,
    .pin = 8,
    .ain = ADC_INPUTCTRL_MUXPOS_AIN2,
};

static struct StelADCInput input_b = {
    .adc = ADC0,
    .port = WNTR_PORT_A,
    .pin = 7,
    .ain = ADC_INPUTCTRL_MUXPOS_AIN7,
};

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

    stel_adc_init();
    stel_adc_init_input(&input_a);
    stel_adc_init_input(&input_b);

    stel_ad5685_init();
    stel_ad5685_soft_reset();
    wntr_delay_ms(1);

    /* Setup the flow program. */
    flow_runner_init();
}

/* Private functions */

static void loop() {
    static struct FlowOutputs outs = {};
    struct FlowInputs in;

    /* Dotstar update */
    static uint16_t hue = 0;
    stel_dotstar_set32(0, wntr_colorspace_hsv_to_rgb(hue, 200, 255));
    stel_dotstar_update();
    hue += 5;

    /* MIDI I/O update */
    struct WntrMIDIMessage midi_msg = {};

    if (wntr_midi_receive(&midi_msg)) {
        in.midi_msg = &midi_msg;
    } else {
        in.midi_msg = NULL;
    }

    /* ADC update */
    /* TODO: This should happen automatically via DMA */
    in.a = ADC_12_BIT_TO_FLOAT(stel_adc_read_sync(&input_a));
    in.b = ADC_12_BIT_TO_FLOAT(stel_adc_read_sync(&input_b));

    /* Advance the flow runner one step. */
    flow_runner_step(&in, &outs);

    /* Update DAC outputs. */
    /* TODO: DMA? */

    stel_ad5685_write_channel(OUTPUT_1_CHANNEL, FLOAT_TO_16_BIT_DAC(outs.one), true);
    stel_ad5685_write_channel(OUTPUT_2_CHANNEL, FLOAT_TO_16_BIT_DAC(outs.two), true);
    stel_ad5685_write_channel(OUTPUT_3_CHANNEL, FLOAT_TO_16_BIT_DAC(outs.three), true);
    stel_ad5685_write_channel(OUTPUT_4_CHANNEL, FLOAT_TO_16_BIT_DAC(outs.four), true);
    stel_dac_set(OUTPUT_DELTA_CHANNEL, FLOAT_TO_12_BIT_DAC(outs.delta));
    stel_dac_set(OUTPUT_GAMMA_CHANNEL, FLOAT_TO_12_BIT_DAC(outs.gamma));
}
