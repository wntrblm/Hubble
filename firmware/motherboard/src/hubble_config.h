/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

/* Global configuration for all of Hubble's hardware and behavior. */

#include "hubble_adc.h"
#include "hubble_dac.h"
#include "hubble_mux50x.h"
#include "sam.h"
#include "wntr_bitbang_spi.h"
#include "wntr_gpio.h"
#include "wntr_sercom_spi.h"
#include <stdint.h>

/*
    Clock configuration
*/
#define WNTR_SYSTEM_CLOCKS_USE_32K_CRYSTAL 1

/*
    ADC/DAC configuration
*/

#define HUBBLE_ADC0_ENABLED 1
#define HUBBLE_ADC1_ENABLED 1

/* 48 MHz clock divided down to 12 MHz, or around 750 KSPS. */
#define HUBBLE_ADC_GCLK GCLK_PCHCTRL_GEN_GCLK1
#define HUBBLE_ADC_PRESCALER ADC_CTRLA_PRESCALER_DIV4

/*
    The ADC inputs are driven by low impedence op-amps (let's assume 1 kOhms),
    so the sample time doesn't need to be very high. (Datasheet Figure 54-4)

    sample_time >= (2 kOhms + 1 kOhms) * 3 pF * 9.7
    sample_time >= 87.3 ns

    With the clock at 12 MHz (83 ns period), 2 clock cycles should be
    sufficient.
*/
#define HUBBLE_ADC_SAMPLE_TIME 2

/*
    Averaging reduces the througput by 1 / SAMPLENUM, so with 750 KSPS
    we'll end up with 46 KSPS, divided amongst the ADC channels.
    See Datasheet table 45-3.
*/
#define HUBBLE_ADC_AVERAGE_SAMPLENUM ADC_AVGCTRL_SAMPLENUM_16
#define HUBBLE_ADC_AVERAGE_ADJRES 0x4

/*
    Special purpose pins
*/
#define PIN_STATUS_LED (WNTR_GPIO_PIN(A, 27))
#define PIN_DS_POWER_EN (WNTR_GPIO_PIN(C, 1))
#define PIN_SDO (WNTR_GPIO_PIN(B, 30))

/*
    GPIO exclusive pins
*/
#define GPIO_1 (WNTR_GPIO_PIN(D, 20))
#define GPIO_2 (WNTR_GPIO_PIN(C, 23))
#define GPIO_3 (WNTR_GPIO_PIN(C, 22))
#define GPIO_4 (WNTR_GPIO_PIN(C, 21))
#define GPIO_5 (WNTR_GPIO_PIN(C, 20))
#define GPIO_6 (WNTR_GPIO_PIN(C, 19))
#define GPIO_7 (WNTR_GPIO_PIN(C, 12))
#define GPIO_8 (WNTR_GPIO_PIN(C, 11))
#define GPIO_9 (WNTR_GPIO_PIN(C, 10))
#define GPIO_10 (WNTR_GPIO_PIN(D, 12))
#define GPIO_11 (WNTR_GPIO_PIN(D, 11))
#define GPIO_12 (WNTR_GPIO_PIN(D, 10))
#define GPIO_13 (WNTR_GPIO_PIN(D, 9))
#define GPIO_14 (WNTR_GPIO_PIN(D, 8))
#define GPIO_15 (WNTR_GPIO_PIN(B, 15))
#define GPIO_16 (WNTR_GPIO_PIN(B, 14))
#define GPIO_17 (WNTR_GPIO_PIN(B, 12))
#define GPIO_18 (WNTR_GPIO_PIN(B, 11))
#define GPIO_19 (WNTR_GPIO_PIN(A, 10))
#define GPIO_20 (WNTR_GPIO_PIN(C, 7))
#define GPIO_21 (WNTR_GPIO_PIN(C, 6))
#define GPIO_22 (WNTR_GPIO_PIN(C, 5))
#define GPIO_23 (WNTR_GPIO_PIN(C, 4))

/*
    Array of all GPIO pins
*/
static const struct WntrGPIOPin GPIO[] = {
    GPIO_1,  GPIO_2,  GPIO_3,  GPIO_4,  GPIO_5,  GPIO_6,  GPIO_7,  GPIO_8,  GPIO_9,  GPIO_10, GPIO_11, GPIO_12,
    GPIO_13, GPIO_14, GPIO_15, GPIO_16, GPIO_17, GPIO_18, GPIO_19, GPIO_20, GPIO_21, GPIO_22, GPIO_23,
};

/*
    ADC exclusive pins with buffers
*/
#define AIN_VREFA (HUBBLE_ADC_INPUT(ADC0, 1, A, 3, B_ANALOG))
#define AIN_1 (HUBBLE_ADC_INPUT(ADC1, 5, C, 3, B_ANALOG))
#define AIN_2 (HUBBLE_ADC_INPUT(ADC1, 6, B, 4, B_ANALOG))
#define AIN_3 (HUBBLE_ADC_INPUT(ADC1, 7, B, 5, B_ANALOG))
#define AIN_4 (HUBBLE_ADC_INPUT(ADC1, 14, D, 0, B_ANALOG))
#define AIN_5 (HUBBLE_ADC_INPUT(ADC1, 15, D, 1, B_ANALOG))
#define AIN_6 (HUBBLE_ADC_INPUT(ADC1, 8, B, 6, B_ANALOG))
#define AIN_7 (HUBBLE_ADC_INPUT(ADC1, 9, B, 7, B_ANALOG))
#define AIN_8 (HUBBLE_ADC_INPUT(ADC0, 2, B, 8, B_ANALOG))
#define AIN_9 (HUBBLE_ADC_INPUT(ADC0, 3, B, 9, B_ANALOG))
#define AIN_10 (HUBBLE_ADC_INPUT(ADC0, 4, A, 4, B_ANALOG))
#define AIN_11 (HUBBLE_ADC_INPUT(ADC0, 6, A, 6, B_ANALOG))
#define AIN_12 (HUBBLE_ADC_INPUT(ADC0, 7, A, 7, B_ANALOG))
#define AIN_13 (HUBBLE_ADC_INPUT(ADC0, 8, A, 8, B_ANALOG))
#define AIN_14 (HUBBLE_ADC_INPUT(ADC0, 9, A, 9, B_ANALOG))
#define AIN_15 (HUBBLE_ADC_INPUT(ADC0, 10, A, 10, B_ANALOG))
#define AIN_16 (HUBBLE_ADC_INPUT(ADC0, 11, A, 11, B_ANALOG))

static const struct HubbleADCInput AIN[] = {
    AIN_1,
    AIN_2,
    AIN_3,
    AIN_4,
    AIN_5,
    AIN_6,
    AIN_7,
    AIN_8,
    AIN_9,
    AIN_10,
    AIN_11,
    AIN_12,
    AIN_13,
    AIN_14,
    AIN_15,
    AIN_16,
};

/*
    Serial exclusive pins
*/
#define SER_1_0 (WNTR_GPIO_PIN_ALT(A, 16, C_SERCOM))
#define SER_1_1 (WNTR_GPIO_PIN_ALT(A, 17, C_SERCOM))
#define SER_1_2 (WNTR_GPIO_PIN_ALT(A, 18, C_SERCOM))
#define SER_1_3 (WNTR_GPIO_PIN_ALT(A, 19, C_SERCOM))

#define SER_2_0 (WNTR_GPIO_PIN_ALT(A, 12, C_SERCOM))
#define SER_2_1 (WNTR_GPIO_PIN_ALT(A, 13, C_SERCOM))
#define SER_2_2 (WNTR_GPIO_PIN_ALT(A, 14, C_SERCOM))
#define SER_2_3 (WNTR_GPIO_PIN_ALT(A, 15, C_SERCOM))

/*
    SPI configuration for Dotstars
*/
static const struct WntrSERCOMSPI DOTSTAR_SPI = {
    .sercom = &SERCOM3->SPI,
    .dopo = SERCOM_SPI_DOPO_SDO_0_SCK_1_CS_2,
    .sdo = WNTR_GPIO_PIN_ALT(A, 22, C_SERCOM),
    .sck = WNTR_GPIO_PIN_ALT(A, 23, C_SERCOM),
    // No CS pin, so this is just an unused pin
    .cs = WNTR_GPIO_PIN_ALT(A, 21, NONE),
    .polarity = 0,
    .phase = 0,
};

/*
    SPI configuration for the external DAC (AD5685)
*/
static const struct WntrSERCOMSPI AD5685_SPI = {
    .sercom = &SERCOM6->SPI,
    .dopo = SERCOM_SPI_DOPO_SDO_0_SCK_1_CS_2,
    .sdo = WNTR_GPIO_PIN_ALT(C, 16, C_SERCOM),
    .sck = WNTR_GPIO_PIN_ALT(C, 17, C_SERCOM),
    // NONE = Don't use hardware CS, since the AD5685 expects 24 bits instead of just 8.
    .cs = WNTR_GPIO_PIN_ALT(C, 18, NONE),
    .polarity = 0,
    .phase = 1,
};

/*
    TODO: I2C configuration for QWIIC
*/
