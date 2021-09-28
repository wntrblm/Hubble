/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>

/*
    Routines for managing USB.

    These are thin wrappers over tinyUSB.
*/

void stel_usb_init();

void stel_usb_task();
