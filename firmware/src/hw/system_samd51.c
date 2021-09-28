/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "samd51.h"

/*
    Initial clock frequency on the SAMD51 is 48 MHz.
*/
#define STARTUP_SYSTEM_CLOCK (48000000)

uint32_t SystemCoreClock = STARTUP_SYSTEM_CLOCK;

void SystemInit(void) {
    SystemCoreClock = STARTUP_SYSTEM_CLOCK;

    /* Use the LDO regulator by default */
    SUPC->VREG.bit.SEL = 0;

    /* Enable cache. */
    CMCC->CTRL.reg = 1;

    /* Enable debug and trace unit. */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    return;
}

void SystemCoreClockUpdate(void) {
    /*
        Not implemented. According to CMSIS, this should evaluate the processor
        clock registers to determine the clock. However, it seems in practice
        that most programs just set the SystemCoreClock variable manually since
        it tends to stay constant after startup.
    */
}
