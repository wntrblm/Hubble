/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "hubble_data_converter_helpers.h"

bool hubble_load_voltage_calibration_table(
    struct HubbleVoltageCalibrationTableEntry* table, size_t table_len, uint8_t bank);

void hubble_save_voltage_calibration_table(
    struct HubbleVoltageCalibrationTableEntry* table, size_t table_len, uint8_t bank);

void hubble_erase_calibration_table(uint32_t bank);
