/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "hubble_dotstar.h"

#define DOTSTART_COUNT 1

/* Static variables */
static const struct WntrSERCOMSPI* spi_;
static uint16_t brightness_ = 0;
static uint8_t pixels_[DOTSTART_COUNT * 3];
static const uint8_t start_frame_[4] = {0x00, 0x00, 0x00, 0x00};

void hubble_dotstar_init(const struct WntrSERCOMSPI* spi, uint8_t brightness) {
    spi_ = spi;
    brightness_ = brightness;
}

void hubble_dotstar_set(size_t n, uint8_t r, uint8_t g, uint8_t b) {
    pixels_[n * 3] = (r * brightness_) >> 8;
    pixels_[n * 3 + 1] = (g * brightness_) >> 8;
    pixels_[n * 3 + 2] = (b * brightness_) >> 8;
}

void hubble_dotstar_set32(size_t n, uint32_t color) {
    hubble_dotstar_set(n, color >> 16 & 0xFF, color >> 8 & 0xFF, color & 0xFF);
}

void hubble_dotstar_update() {
    WntrSERCOMSPI_write(spi_, start_frame_, 4);
    for (size_t i = 0; i < DOTSTART_COUNT; i++) {
        WntrSERCOMSPI_write(spi_, (uint8_t[]){0xFF}, 1);
        WntrSERCOMSPI_write(spi_, pixels_ + (i * 3), 3);
    }
    for (size_t i = 0; i < DOTSTART_COUNT / 2 + 1; i++) { WntrSERCOMSPI_write(spi_, (uint8_t[]){0x00}, 1); }
}
