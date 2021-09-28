/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "stel_dac.h"
#include "wntr_gpio.h"

void stel_dac_init() {
    /* Enable the APB clock for the DAC. */
    MCLK->APBDMASK.reg |= MCLK_APBDMASK_DAC;

    /* Connect the peripheral clock. GCLK3 = 32kHz, so the conversion
       time is 750uS and the maximum conversion rate is 2.6 kHz. The
       maximum possible rate is 1 MHz. (Datasheet 47.6.2.4) */
    GCLK->PCHCTRL[DAC_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK3;
    while (!GCLK->PCHCTRL[DAC_GCLK_ID].bit.CHEN) {};

    /* Reset */
    DAC->CTRLA.bit.SWRST = 1;
    while (DAC->SYNCBUSY.bit.SWRST) {};

    /* Select the VREF - See errata CHIP003-161 - must be set to unbuffered
       external reference.  */
    DAC->CTRLB.reg |= DAC_CTRLB_REFSEL_VREFPU;

    /* Enable channels and set the refresh rate to every 60uS, needed
       because we're outputing DC. */
    DAC->DACCTRL[0].reg |= (DAC_DACCTRL_ENABLE | DAC_DACCTRL_REFRESH(2));
    DAC->DACCTRL[1].reg |= (DAC_DACCTRL_ENABLE | DAC_DACCTRL_REFRESH(2));

    /* TODO: Dithering? */

    /* Enable the DAC. */
    DAC->CTRLA.reg |= DAC_CTRLA_ENABLE;
    while (DAC->SYNCBUSY.bit.ENABLE) {};

    /* Wait for it to be ready. */
    while (!DAC->STATUS.bit.READY0) {};
    while (!DAC->STATUS.bit.READY1) {};
}

void stel_dac_init_output(const struct StelDACOutput* output) {
    wntr_gpio_configure_alt(output->port, output->pin, WNTR_PMUX_A);
}

void stel_dac_set(const struct StelDACOutput* output, uint16_t val) {
    if (output->channel == 0) {
        while (DAC->SYNCBUSY.bit.DATA0) {};
        DAC->DATA[0].reg = val;
        while (DAC->STATUS.bit.EOC0) {};
    } else if (output->channel == 1) {
        while (DAC->SYNCBUSY.bit.DATA1) {};
        DAC->DATA[1].reg = val;
        while (DAC->STATUS.bit.EOC1) {};
    }
}
