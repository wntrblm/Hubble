/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "hubble_ad5685.h"
#include "hubble_config.h"

/* Macros and constants. */

#define CMD_SOFT_RESET 0b01100000
#define CMD_WRITE 0b00010000
#define CMD_UPDATE 0b00100000
#define CMD_WRITE_AND_UPDATE 0b00110000
#define CMD_ADDR_DAC_A 0b0001
#define CMD_ADDR_DAC_B 0b0010
#define CMD_ADDR_DAC_C 0b0100
#define CMD_ADDR_DAC_D 0b1000
#define CMD_ADDR_DAC_ALL 0b1111

/* Static variables */
static const struct WntrSERCOMSPI* spi_;

/* Private functions */

inline static void send_command(uint8_t command, uint8_t data1, uint8_t data2) {
    WntrGPIOPin_set(spi_->cs, false);
    WntrSERCOMSPI_write(spi_, (const uint8_t[]){command, data1, data2}, 3);
    WntrGPIOPin_set(spi_->cs, true);
}

/* Public functions */

void hubble_ad5685_init(const struct WntrSERCOMSPI* spi) {
    spi_ = spi;
    WntrGPIOPin_set_as_output(spi_->cs);
    WntrGPIOPin_set(spi_->cs, true);
}

void hubble_ad5685_soft_reset() { send_command(CMD_SOFT_RESET, 0x0, 0x0); }

void hubble_ad5685_write_channel(enum HubbleAD5685Channel channel, uint16_t val, bool update) {
    const uint8_t cmd = update ? CMD_WRITE_AND_UPDATE : CMD_WRITE;
    send_command(cmd | (1 << channel), (val >> 8) & 0xFF, val & 0xFF);
}

void hubble_ad5685_update_channel(enum HubbleAD5685Channel channel) {
    send_command(CMD_UPDATE | (1 << channel), 0x0, 0x0);
}

void hubble_ad5685_update_all_channels() { send_command(CMD_UPDATE | CMD_ADDR_DAC_ALL, 0x0, 0x0); }
