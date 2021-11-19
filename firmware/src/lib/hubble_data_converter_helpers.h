/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include "printf.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define HUBBLE_RESOLUTION_8_BIT 256
#define HUBBLE_RESOLUTION_10_BIT 1024
#define HUBBLE_RESOLUTION_12_BIT 4096
#define HUBBLE_RESOLUTION_14_BIT 16384
#define HUBBLE_RESOLUTION_16_BIT 65536

/*
  Convert a code point to a voltage.

  This is useful for ADCs - if you know the range of the ADC's
  measurements you can use this to determine which voltage
  an analogRead() result corresponds to.
*/
inline static float hubble_code_points_to_volts(
    uint32_t code_point, uint32_t resolution, float min_voltage, float max_voltage, bool invert) {
    float voltage_range = max_voltage - min_voltage;
    if (invert) {
        code_point = (resolution - 1) - code_point;
    }
    float normalized_value = (float)(code_point) / (float)(resolution - 1);
    return min_voltage + (voltage_range * normalized_value);
}

/*
  Convert a voltage to a code point.

  This is useful for DACs - if you want to output a specific
  voltage, then you can use this to determine which code point
  to pass to analogWrite()
*/
inline static uint32_t
hubble_volts_to_code_points(float volts, uint32_t resolution, float min_voltage, float max_voltage, bool invert) {
    float voltage_range = max_voltage - min_voltage;
    float normalized_value = (volts - min_voltage) / voltage_range;
    uint32_t result = ceilf(normalized_value * (resolution - 1));

    if (invert) {
        result = (resolution - 1) - result;
    }

    return result;
}

/*
  Determines the gain and offset error using two measurements.

  For example, if you were using this for a DAC, you would pick
  two output voltages to measure - one near the bottom of the range,
  one near the top. Use the volts_to_code_points() function to set
  the DAC output's value. Measure the *actual* voltage for both
  of the expected values. You would use those values here to get
  the gain and offset errors.
*/
inline static void hubble_calculate_gain_and_offset_error(
    float low_measured,
    float high_measured,
    float low_expected,
    float high_expected,
    float* gain_error,
    float* offset_error) {
    (*gain_error) = (high_measured - low_measured) / (high_expected - low_expected);
    (*offset_error) = low_measured - (low_expected * (*gain_error));
}

/*
  Use the gain and offset error to correct a measured value.
*/
inline static float hubble_apply_error_correction(float value, float gain_error, float offset_error) {
    return (value / gain_error) - offset_error;
}

struct HubbleVoltageCalibrationTableEntry {
    float expected;
    float measured;
};

struct HubbleVoltageCalibrationTable {
    struct HubbleVoltageCalibrationTableEntry* entries;
    size_t len;
};

inline static void HubbleVoltageCalibrationTable_find_nearest_pair(
    float value,
    struct HubbleVoltageCalibrationTable table,
    struct HubbleVoltageCalibrationTableEntry* out_low,
    struct HubbleVoltageCalibrationTableEntry* out_high) {
    struct HubbleVoltageCalibrationTableEntry* low = &(table.entries)[0];
    struct HubbleVoltageCalibrationTableEntry* high = &(table.entries)[1];
    struct HubbleVoltageCalibrationTableEntry* current;
    bool found = false;

    for (size_t i = 0; i < table.len; i++) {
        current = &(table.entries)[i];
        if (current->measured <= value) {
            low = current;
        }
        if (current->measured > value) {
            high = current;
            found = true;
            break;
        }
    }

    if (!found) {
        high = low;
    }

    (*out_low) = (*low);
    (*out_high) = (*high);
}

inline static float HubbleVoltageCalibrationTable_lookup(float value, struct HubbleVoltageCalibrationTable table) {
    struct HubbleVoltageCalibrationTableEntry low, high;

    HubbleVoltageCalibrationTable_find_nearest_pair(value, table, &low, &high);

    float frac = (value - low.measured) / (high.measured - low.measured);

    float result = low.expected + ((high.expected - low.expected) * frac);

    return result;
}

inline static void HubbleVoltageCalibrationTable_print(struct HubbleVoltageCalibrationTable table) {
    printf("---- HubbleVoltageCalibrationTable 0x%x + %x\n", table.entries, table.len);
    for (size_t i = 0; i < table.len; i++) {
        printf("%0.3f : %0.3f\n", (double)(table.entries[i].expected), (double)(table.entries[i].measured));
    }
    printf("----\n");
}
