/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Routines for interacting with the SAM D51 analog-to-digital converter. */

#include "wntr_gpio.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
    Input channel descriptor. These settings should be derived from the
    pin multiplexing table in the datasheet.
*/
struct HubbleADCInput {
    /* Which ADC this pin uses. */
    Adc* adc;
    /* Physical pin*/
    struct WntrGPIOPin pin;
    /* AIN number for the input */
    uint32_t ain;
};

#define HUBBLE_ADC_INPUT(adc_, ain_, port_, pin_, alt_)                                                                \
    ((struct HubbleADCInput){                                                                                          \
        .adc = adc_,                                                                                                   \
        .ain = ADC_INPUTCTRL_MUXPOS_AIN##ain_,                                                                         \
        .pin = {.port = WNTR_PORT_##port_, .pin = pin_, .alt = WNTR_PMUX_##alt_}})

void hubble_adc_init();

/* Configure hardware error correction. */
void hubble_adc_enable_error_correction(uint16_t gain, uint16_t offset);

/* Configure a given input channel for ADC reading. */
void hubble_adc_init_input(const struct HubbleADCInput* const input);

uint16_t hubble_adc_read_sync(const struct HubbleADCInput* input);
