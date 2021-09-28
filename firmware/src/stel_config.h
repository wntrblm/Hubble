/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Global configuration for all of Stellar's hardware and behavior. */

#include "sam.h"
#include "wntr_gpio.h"
#include "stel_adc.h"
#include <stdint.h>


/*
    ADC configuration
*/

#define STEL_ADC0_ENABLED 1
#define STEL_ADC1_ENABLED 1

/* 48 MHz clock divided down to 12 MHz, or around 750 KSPS. */
#define STEL_ADC_GCLK GCLK_PCHCTRL_GEN_GCLK1
#define STEL_ADC_PRESCALER ADC_CTRLA_PRESCALER_DIV4

/*
    The ADC inputs are driven by low impedence op-amps (let's assume 1 kOhms),
    so the sample time doesn't need to be very high. (Datasheet Figure 54-4)

    sample_time >= (2 kOhms + 1 kOhms) * 3 pF * 9.7
    sample_time >= 87.3 ns

    With the clock at 12 MHz (83 ns period), 2 clock cycles should be
    sufficient.
*/
#define STEL_ADC_SAMPLE_TIME 2

/*
    Averaging reduces the througput by 1 / SAMPLENUM, so with 750 KSPS
    we'll end up with 46 KSPS, divided amongst the ADC channels.
    See Datasheet table 45-3.
*/
#define STEL_ADC_AVERAGE_SAMPLENUM ADC_AVGCTRL_SAMPLENUM_16
#define STEL_ADC_AVERAGE_ADJRES 0x4
