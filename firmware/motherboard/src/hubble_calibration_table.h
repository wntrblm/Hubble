/*
    Copyright (c) 2024 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "wntr_data_converter_helpers.h"
#include <stdbool.h>

void hubble_calibration_tables_init(bool load_from_nvm);
extern struct WntrVoltageCalibrationTable* hubble_dac_calibration_tables[];
extern struct WntrVoltageCalibrationTable* hubble_adc_calibration_tables[];
