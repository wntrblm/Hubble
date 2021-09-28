/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Global configuration for all of Stellar's hardware and behavior. */

#include "sam.h"
#include "stel_adc.h"
#include "stel_dac.h"
#include "wntr_gpio.h"
#include <stdint.h>

/*
    ADC/DAC configuration
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

/*
    A list of physical input pins for the ADC to measure during each
    scan.
*/
static const struct StelADCInput stel_adc0_inputs[] = {
    {ADC0, WNTR_PORT_B, 0, ADC_INPUTCTRL_MUXPOS_AIN12},   // A1
    {ADC0, WNTR_PORT_B, 1, ADC_INPUTCTRL_MUXPOS_AIN13},   // A2
    {ADC0, WNTR_PORT_B, 2, ADC_INPUTCTRL_MUXPOS_AIN14},   // A3
    {ADC0, WNTR_PORT_B, 3, ADC_INPUTCTRL_MUXPOS_AIN15},   // A4
    {ADC0, WNTR_PORT_A, 3, ADC_INPUTCTRL_MUXPOS_AIN1},    // A6
    {ADC0, WNTR_PORT_A, 4, ADC_INPUTCTRL_MUXPOS_AIN4},    // A13
    {ADC0, WNTR_PORT_A, 6, ADC_INPUTCTRL_MUXPOS_AIN6},    // A15
    {ADC0, WNTR_PORT_A, 7, ADC_INPUTCTRL_MUXPOS_AIN7},    // A16
    {ADC0, WNTR_PORT_A, 11, ADC_INPUTCTRL_MUXPOS_AIN11},  // A19
    {ADC0, WNTR_PORT_A, 10, ADC_INPUTCTRL_MUXPOS_AIN10},  // A20
};

static const struct StelADCInput stel_adc1_inputs[] = {
    {ADC1, WNTR_PORT_B, 4, ADC_INPUTCTRL_MUXPOS_AIN6},  // A7
    {ADC1, WNTR_PORT_B, 5, ADC_INPUTCTRL_MUXPOS_AIN7},  // A8
    {ADC1, WNTR_PORT_B, 6, ADC_INPUTCTRL_MUXPOS_AIN8},  // A9
    {ADC1, WNTR_PORT_B, 7, ADC_INPUTCTRL_MUXPOS_AIN9},  // A10
    {ADC1, WNTR_PORT_B, 8, ADC_INPUTCTRL_MUXPOS_AIN0},  // A11
    {ADC1, WNTR_PORT_B, 9, ADC_INPUTCTRL_MUXPOS_AIN1},  // A12
    {ADC1, WNTR_PORT_A, 9, ADC_INPUTCTRL_MUXPOS_AIN3},  // A17
    {ADC1, WNTR_PORT_A, 8, ADC_INPUTCTRL_MUXPOS_AIN2},  // A18
};

#define A1 (&stel_adc0_inputs[0])
#define A2 (&stel_adc0_inputs[1])
#define A3 (&stel_adc0_inputs[2])
#define A4 (&stel_adc0_inputs[3])
#define A5 (&stel_dac_outputs[0])
#define A6 (&stel_adc0_inputs[4])
#define A7 (&stel_adc1_inputs[0])
#define A8 (&stel_adc1_inputs[1])
#define A9 (&stel_adc1_inputs[2])
#define A10 (&stel_adc1_inputs[3])
#define A11 (&stel_adc1_inputs[4])
#define A12 (&stel_adc1_inputs[5])
#define A13 (&stel_adc0_inputs[5])
#define A14 (&stel_dac_outputs[1])
#define A15 (&stel_adc0_inputs[6])
#define A16 (&stel_adc0_inputs[7])
#define A17 (&stel_adc1_inputs[6])
#define A18 (&stel_adc1_inputs[7])
#define A19 (&stel_adc0_inputs[8])
#define A20 (&stel_adc0_inputs[9])

/*
    External DAC (AD5685) configuration.
*/

#define STEL_AD5685_SERCOM (SERCOM4)
#define STEL_AD5685_SERCOM_DOPO (SERCOM_SPI_DOPO_SDO_0_SCK_1_CS_2)
#define STEL_AD5685_SDO (WNTR_GPIO_PIN(WNTR_PORT_A, 13))
#define STEL_AD5685_SDO_ALT (WNTR_PMUX_D)
#define STEL_AD5685_SCK (WNTR_GPIO_PIN(WNTR_PORT_A, 12))
#define STEL_AD5685_SCK_ALT (WNTR_PMUX_D)
#define STEL_AD5685_CS (WNTR_GPIO_PIN(WNTR_PORT_A, 14))
