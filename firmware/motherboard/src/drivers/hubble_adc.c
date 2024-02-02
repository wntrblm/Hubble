/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "hubble_adc.h"
#include "hubble_config.h"
#include "wntr_assert.h"
#include "wntr_gpio.h"

/* Forward declarations. */

static void adc_inst_configure(Adc* inst);

/* Public methods. */

void hubble_adc_init() {
    uint32_t biascomp;
    uint32_t biasr2r;
    uint32_t biasrefbuf;

#if HUBBLE_ADC0_ENABLED == 1
    MCLK->APBDMASK.reg |= MCLK_APBDMASK_ADC0;
    GCLK->PCHCTRL[ADC0_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | HUBBLE_ADC_GCLK;
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

#if HUBBLE_ADC1_ENABLED == 1
    MCLK->APBDMASK.reg |= MCLK_APBDMASK_ADC1;
    GCLK->PCHCTRL[ADC1_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | HUBBLE_ADC_GCLK;
    while (!GCLK->PCHCTRL[ADC1_GCLK_ID].bit.CHEN) {};

    adc_inst_configure(ADC1);

    biascomp = (*((uint32_t*)ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
    biasr2r = (*((uint32_t*)ADC1_FUSES_BIASR2R_ADDR) & ADC1_FUSES_BIASR2R_Msk) >> ADC1_FUSES_BIASR2R_Pos;
    biasrefbuf = (*((uint32_t*)ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;

    ADC1->CALIB.reg = ADC_CALIB_BIASREFBUF(biasrefbuf) | ADC_CALIB_BIASR2R(biasr2r) | ADC_CALIB_BIASCOMP(biascomp);

    /* Enable the ADC. */
    ADC1->CTRLA.bit.ENABLE = 1;
    while (ADC1->SYNCBUSY.bit.ENABLE) {};
#endif

    /*
        NOTE: The datasheet says to throw away the first five readings, however,
        since we a *lot* of reads and use averaging, that isn't really necessary.
    */
}

void hubble_adc_init_input(const struct HubbleADCInput* input) {
    WntrGPIOPin_set_as_input(input->pin, false);
    WntrGPIOPin_configure_alt(input->pin);
}

uint16_t hubble_adc_read_sync(const struct HubbleADCInput* input) {
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
    inst->CTRLA.reg = HUBBLE_ADC_PRESCALER;
    inst->CTRLB.reg |= ADC_CTRLB_RESSEL_16BIT;
    while (inst->SYNCBUSY.bit.CTRLB) {};

    inst->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(HUBBLE_ADC_SAMPLE_TIME);
    while (inst->SYNCBUSY.bit.SAMPCTRL) {};

    inst->AVGCTRL.reg = HUBBLE_ADC_AVERAGE_SAMPLENUM | ADC_AVGCTRL_ADJRES(HUBBLE_ADC_AVERAGE_ADJRES);
    while (inst->SYNCBUSY.bit.AVGCTRL) {};

    /* Configure the voltage references. */
    inst->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1 | ADC_REFCTRL_REFCOMP;
    while (inst->SYNCBUSY.bit.REFCTRL) {};
    inst->INPUTCTRL.reg = ADC_INPUTCTRL_MUXNEG_GND;
    while (inst->SYNCBUSY.bit.INPUTCTRL) {};
}
