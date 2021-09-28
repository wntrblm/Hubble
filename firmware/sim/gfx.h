/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include <cairo/cairo.h>

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600

void gfx_init();
void gfx_deinit();
cairo_t* gfx_start(float r, float g, float b);
void gfx_end();
