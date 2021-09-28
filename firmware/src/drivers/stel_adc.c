/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "stel_adc.h"
#include "wntr_assert.h"
#include "wntr_gpio.h"

/* Stellar only uses ADC0, so there's no need to configure ADC1. */
#define ADC0_ENABLED 1
#define ADC1_ENABLED 0

/* 48 MHz clock divided down to 12 MHz, or around 750 KSPS. */
#define ADC_GCLK GCLK_PCHCTRL_GEN_GCLK1
#define ADC_PRESCALER ADC_CTRLA_PRESCALER_DIV4
/*
    The ADC inputs are driven by low impedence op-amps (let's assume 1 kOhms),
    so the sample time doesn't need to be very high. (Datasheet Figure 54-4)

    sample_time >= (2 kOhms + 1 kOhms) * 3 pF * 9.7
    sample_time >= 87.3 ns

    With the clock at 12 MHz (83 ns period), 2 clock cycles should be
    sufficient.
*/
#define ADC_SAMPLE_TIME 2
/*
    Averaging reduces the througput by 1 / SAMPLENUM, so with 750 KSPS
    we'll end up with 46 KSPS, which is nice and close to standard audio rate
    (44.1 kHz). See Datasheet table 45-3.
*/
#define ADC_AVERAGE_SAMPLENUM ADC_AVGCTRL_SAMPLENUM_16
#define ADC_AVERAGE_ADJRES 0x4

/* Forward declarations. */

static void adc_inst_configure(Adc* inst);

/* Public methods. */

void stel_adc_init() {
    uint32_t biascomp;
    uint32_t biasr2r;
    uint32_t biasrefbuf;

#if ADC0_ENABLED == 1
    MCLK->APBDMASK.reg |= MCLK_APBDMASK_ADC0;
    GCLK->PCHCTRL[ADC0_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | ADC_GCLK;
    while (!GCLK->PCHCTRL[ADC0_GCLK_ID].bit.CHEN) {};

    adc_inst_configure(ADC0);

    biascomp = (*((uint32_t*)ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
    biasr2r = (*((uint32_t*)ADC0_FUSES_BIASR2R_ADDR) & ADC0_FUSES_BIASR2R_Msk) >> ADC0_FUSES_BIASR2R_Pos;
    biasrefbuf = (*((uint32_t*)ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;

    ADC0->CALIB.reg = ADC_CALIB_BIASREFBUF(biasrefbuf) | ADC_CALIB_BIASR2R(biasr2r) | ADC_CALIB_BIASCOMP(biascomp);

    /* Enable the ADC. */
    ADC0->CTRLA.bit.ENABLE = 1;
    while (ADC0->SYNCBUSY.bit.ENABLE) {};
#endif

#if ADC1_ENABLED == 1
    MCLK->APBDMASK.reg |= MCLK_APBDMASK_ADC1;
    GCLK->PCHCTRL[ADC1_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | ADC_GCLK;
    while (!GCLK->PCHCTRL[ADC1_GCLK_ID].bit.CHEN) {};

    adc_inst_configure(ADC1);

    biascomp = (*((uint32_t*)ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
    biasr2r = (*((uint32_t*)ADC1_FUSES_BIASR2R_ADDR) & ADC1_FUSES_BIASR2R_Msk) >> ADC1_FUSES_BIASR2R_Pos;
    biasrefbuf = (*((uint32_t*)ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;

    ADC1->CALIB.reg = ADC_CALIB_BIASREFBUF(biasrefbuf) | ADC_CALIB_BIASR2R(biasr2r) | ADC_CALIB_BIASCOMP(biascomp);
#endif

    /*
        NOTE: The datasheet says to throw away the first five readings, however,
        since we a *lot* of reads and use averaging, that isn't really necessary.
    */
}

void stel_adc_init_input(const struct StelADCInput* input) {
    wntr_gpio_set_as_input(input->port, input->pin, false);
    wntr_gpio_configure_alt(input->port, input->pin, WNTR_PMUX_B);
}

uint16_t stel_adc_read_sync(const struct StelADCInput* input) {
    /* Flush the ADC - if there's a conversion in process it'll be cancelled. */
    input->adc->SWTRIG.reg = ADC_SWTRIG_FLUSH;
    while (input->adc->SWTRIG.bit.FLUSH) {};

    /* Set the positive mux to the input pin */
    input->adc->INPUTCTRL.bit.MUXPOS = input->ain;
    while (input->adc->SYNCBUSY.bit.INPUTCTRL) {};

    /* Start the ADC using a software trigger. */
    input->adc->SWTRIG.bit.START = 1;

    /* Wait for the result ready flag to be set. */
    while (input->adc->INTFLAG.bit.RESRDY == 0) {};

    /* Clear the flag. */
    input->adc->INTFLAG.reg = ADC_INTFLAG_RESRDY;

    /*
        Throw away the first result and measure again - the datasheet
        recommends doing that since the first conversion for a new
        configuration will be incorrect.
    */
    input->adc->SWTRIG.bit.START = 1;
    while (input->adc->INTFLAG.bit.RESRDY == 0) {};
    input->adc->INTFLAG.reg = ADC_INTFLAG_RESRDY;

    return input->adc->RESULT.reg;
}

/* Private functions */

static void adc_inst_configure(Adc* inst) {
    /* Reset the ADC. */
    inst->CTRLA.bit.ENABLE = 0;
    while (inst->SYNCBUSY.bit.ENABLE) {};
    inst->CTRLA.bit.SWRST = 1;
    while (inst->SYNCBUSY.bit.SWRST) {};

    /*
        Configure prescaler, resolution, sample time, and averaging. All of
        these impact the overall conversion throughput.
    */
    inst->CTRLA.reg = ADC_PRESCALER;
    inst->CTRLB.reg |= ADC_CTRLB_RESSEL_16BIT;
    while (inst->SYNCBUSY.bit.CTRLB) {};

    inst->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(ADC_SAMPLE_TIME);
    while (inst->SYNCBUSY.bit.SAMPCTRL) {};

    inst->AVGCTRL.reg = ADC_AVERAGE_SAMPLENUM | ADC_AVGCTRL_ADJRES(ADC_AVERAGE_ADJRES);
    while (inst->SYNCBUSY.bit.AVGCTRL) {};

    /* Configure the voltage references. */
    inst->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1 | ADC_REFCTRL_REFCOMP;
    while (inst->SYNCBUSY.bit.REFCTRL) {};
    inst->INPUTCTRL.reg = ADC_INPUTCTRL_MUXNEG_GND;
    while (inst->SYNCBUSY.bit.INPUTCTRL) {};

    /* TODO: Enable rail to rail? */
}
