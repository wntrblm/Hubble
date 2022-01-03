/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Routines for controlling a MUX508/MUX509 */

#include "wntr_gpio.h"

struct HubbleMUX50x {
    struct WntrGPIOPin a0;
    struct WntrGPIOPin a1;
};

inline static void hubble_mux50x_set(const struct HubbleMUX50x, uint8_t);

inline static void hubble_mux50x_init(const struct HubbleMUX50x mux) {
    WntrGPIOPin_set_as_output(mux.a0);
    WntrGPIOPin_set_as_output(mux.a1);
    hubble_mux50x_set(mux, 0);
}

inline static void hubble_mux50x_set(const struct HubbleMUX50x mux, uint8_t addr) {
    WntrGPIOPin_set(mux.a0, (addr & 0x1));
    WntrGPIOPin_set(mux.a1, (addr & 0x2) >> 1);
}
