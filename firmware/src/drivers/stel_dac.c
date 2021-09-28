/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "stel_dac.h"
#include "wntr_gpio.h"

void stel_dac_init() {
    /* Configure outputs on PA02 and PA05 */
    wntr_gpio_configure_alt(WNTR_PORT_A, 2, WNTR_PMUX_A);
    wntr_gpio_configure_alt(WNTR_PORT_A, 5, WNTR_PMUX_A);

    /* Enable the APB clock for the DAC. */
    MCLK->APBDMASK.reg |= MCLK_APBDMASK_DAC;

    /* Connect the peripheral clock. (GCLK3 = 32kHz) */
    GCLK->PCHCTRL[DAC_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK3;
    while (!GCLK->PCHCTRL[DAC_GCLK_ID].bit.CHEN) {};

    /* Reset */
    DAC->CTRLA.bit.SWRST = 1;
    while (DAC->SYNCBUSY.bit.SWRST) {};

    /* Select the VREF - See errata CHIP003-161 */
    DAC->CTRLB.reg |= DAC_CTRLB_REFSEL_VREFPU;

    /* Enable channels and set the refresh rate to every 60uS */
    DAC->DACCTRL[0].reg |= (DAC_DACCTRL_ENABLE | DAC_DACCTRL_REFRESH(2));
    DAC->DACCTRL[1].reg |= (DAC_DACCTRL_ENABLE | DAC_DACCTRL_REFRESH(2));

    /* Enable the DAC. */
    DAC->CTRLA.reg |= DAC_CTRLA_ENABLE;
    while (DAC->SYNCBUSY.bit.ENABLE) {};

    /* Wait for it to be ready. */
    while (!DAC->STATUS.bit.READY0) {};
    while (!DAC->STATUS.bit.READY1) {};
}

void stel_dac_set(enum StelDACChannel channel, uint16_t val) {
    if (channel == DAC_CHANNEL_A) {
        while (DAC->SYNCBUSY.bit.DATA0) {};
        DAC->DATA[0].reg = val;
    } else if (channel == DAC_CHANNEL_B) {
        while (DAC->SYNCBUSY.bit.DATA1) {};
        DAC->DATA[1].reg = val;
    }
}
