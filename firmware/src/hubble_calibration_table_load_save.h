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

bool HubbleVoltageCalibrationTable_load_from_nvm(struct HubbleVoltageCalibrationTable table, uint8_t bank);

void HubbleVoltageCalibrationTable_save_to_nvm(struct HubbleVoltageCalibrationTable table, uint8_t bank);

void HubbleVoltageCalibrationTable_erase_nvm_bank(uint32_t bank);
