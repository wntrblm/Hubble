/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/*
    Driver for the SAMD51's on-board DAC.
*/

#include <stdbool.h>
#include <stdint.h>

enum StelDACChannel {
    DAC_CHANNEL_A = 0,
    DAC_CHANNEL_B = 1,
};

void stel_dac_init();
void stel_dac_set(enum StelDACChannel channel, uint16_t val);
