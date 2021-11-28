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

#include "wntr_sercom_spi.h"
#include <stdbool.h>
#include <stdint.h>

enum HubbleAD5685Channel {
    AD5685_CHANNEL_A = 0,
    AD5685_CHANNEL_B = 1,
    AD5685_CHANNEL_C = 2,
    AD5685_CHANNEL_D = 3,
};

void hubble_ad5685_init(const struct WntrSERCOMSPI* spi);

void hubble_ad5685_soft_reset();

void hubble_ad5685_write_channel(enum HubbleAD5685Channel channel, uint16_t val, bool update);
void hubble_ad5685_update_channel(enum HubbleAD5685Channel channel);
void hubble_ad5685_update_all_channels();
