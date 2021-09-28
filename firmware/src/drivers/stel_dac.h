/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/*
    Driver for the SAMD51's on-board DAC.
*/

#include "wntr_gpio.h"
#include <stdbool.h>
#include <stdint.h>

/*
    Output channel descriptor. These settings should be derived from the
    pin multiplexing table in the datasheet.
*/
struct StelDACOutput {
    /* IO port for the input */
    uint8_t port;
    /* Pin number for the input */
    uint32_t pin;
    /* Which DAC channel  */
    uint8_t channel;
};

/* The SAMD51 only has two DAC channels and their pin assignment is fixed. */
static const struct StelDACOutput stel_dac_outputs[] = {
    /* VOUT0 */
    {WNTR_PORT_A, 2, 0},
    /* VOUT1 */
    {WNTR_PORT_A, 5, 1},
};

void stel_dac_init();
void stel_dac_init_output(const struct StelDACOutput* output);
void stel_dac_set(const struct StelDACOutput* output, uint16_t val);
