/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Routines for interacting with the SAM D51 analog-to-digital converter. */

#include "sam.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
    Input channel descriptor. These settings should be derived from the
    pin multiplexing table in the datasheet.
*/
struct StelADCInput {
    /* Which ADC this pin uses. */
    Adc* adc;
    /* IO port for the input */
    uint8_t port;
    /* Pin number for the input */
    uint32_t pin;
    /* AIN number for the input */
    uint32_t ain;
};

void stel_adc_init();

/* Configure hardware error correction. */
void stel_adc_enable_error_correction(uint16_t gain, uint16_t offset);

/* Configure a given input channel for ADC reading. */
void stel_adc_init_input(const struct StelADCInput* const input);

uint16_t stel_adc_read_sync(const struct StelADCInput* input);
