/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Routines for controlling Dotstar (APA102C) RGB LEDs. */

#include <stddef.h>
#include <stdint.h>

void stel_dotstar_init(uint8_t brightness);
void stel_dotstar_set(size_t n, uint8_t r, uint8_t g, uint8_t b);
/* Same as stel_dotstar_set, but takes a whole 24-bit integer as the color value. */
void stel_dotstar_set32(size_t n, uint32_t color);
void stel_dotstar_update();
