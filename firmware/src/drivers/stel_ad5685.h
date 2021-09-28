/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/*
    Driver for the Analog Devices AD5685R 14-bit, quad, digital-to-analog
    converter.
*/

#include <stdbool.h>
#include <stdint.h>

enum StelAD5685Channel {
    AD5685_CHANNEL_A = 0,
    AD5685_CHANNEL_B = 1,
    AD5685_CHANNEL_C = 2,
    AD5685_CHANNEL_D = 3,
};

void stel_ad5685_init();

void stel_ad5685_soft_reset();

void stel_ad5685_write_channel(enum StelAD5685Channel channel, uint16_t val, bool update);
void stel_ad5685_update_channel(enum StelAD5685Channel channel);
void stel_ad5685_update_all_channels();
