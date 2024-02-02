/*
    Copyright (c) 2024 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "hubble_calibration_table.h"
#include "hubble_calibration_table_load_save.h"
#include "wntr_array.h"
#include "wntr_data_converter_helpers.h"
#include <stdlib.h>
#include <string.h>

/* Macros and constants */

static const struct WntrVoltageCalibrationTableEntry dac_reference_calibration_entires_[] = {
    {.expected = -8.0, .measured = -8.0},
    {.expected = -7.0, .measured = -7.0},
    {.expected = -6.0, .measured = -6.0},
    {.expected = -5.0, .measured = -5.0},
    {.expected = -4.0, .measured = -4.0},
    {.expected = -3.0, .measured = -3.0},
    {.expected = -2.0, .measured = -2.0},
    {.expected = -1.0, .measured = -1.0},
    {.expected = 0.0, .measured = -0.0},
    {.expected = 1.0, .measured = 1.0},
    {.expected = 2.0, .measured = 2.0},
    {.expected = 3.0, .measured = 3.0},
    {.expected = 4.0, .measured = 4.0},
    {.expected = 5.0, .measured = 5.0},
    {.expected = 6.0, .measured = 6.0},
    {.expected = 7.0, .measured = 7.0},
    {.expected = 8.0, .measured = 8.0},
};

#define DEF_CALIBRATION_TABLE(name)                                                                                    \
    static struct WntrVoltageCalibrationTableEntry                                                                     \
        name##_calibration_table_entries_[WNTR_ARRAY_LEN(dac_reference_calibration_entires_)];                         \
    static struct WntrVoltageCalibrationTable name##_calibration_table = {                                             \
        .entries = name##_calibration_table_entries_,                                                                  \
        .len = WNTR_ARRAY_LEN(name##_calibration_table_entries_),                                                      \
    };

/* Static variables */

DEF_CALIBRATION_TABLE(dac_1);
DEF_CALIBRATION_TABLE(dac_2);
DEF_CALIBRATION_TABLE(dac_3);
DEF_CALIBRATION_TABLE(dac_4);
DEF_CALIBRATION_TABLE(dac_5);
DEF_CALIBRATION_TABLE(dac_6);
DEF_CALIBRATION_TABLE(dac_7);
DEF_CALIBRATION_TABLE(dac_8);
DEF_CALIBRATION_TABLE(dac_9);
DEF_CALIBRATION_TABLE(dac_10);
DEF_CALIBRATION_TABLE(dac_11);
DEF_CALIBRATION_TABLE(dac_12);

struct WntrVoltageCalibrationTable* hubble_dac_calibration_tables[] = {
    &dac_2_calibration_table,
    &dac_3_calibration_table,
    &dac_4_calibration_table,
    &dac_5_calibration_table,
    &dac_6_calibration_table,
    &dac_7_calibration_table,
    &dac_8_calibration_table,
    &dac_9_calibration_table,
    &dac_10_calibration_table,
    &dac_11_calibration_table,
    &dac_12_calibration_table,
};

DEF_CALIBRATION_TABLE(adc_1);
DEF_CALIBRATION_TABLE(adc_2);
DEF_CALIBRATION_TABLE(adc_3);
DEF_CALIBRATION_TABLE(adc_4);
DEF_CALIBRATION_TABLE(adc_5);
DEF_CALIBRATION_TABLE(adc_6);
DEF_CALIBRATION_TABLE(adc_7);
DEF_CALIBRATION_TABLE(adc_8);
DEF_CALIBRATION_TABLE(adc_9);
DEF_CALIBRATION_TABLE(adc_10);
DEF_CALIBRATION_TABLE(adc_11);
DEF_CALIBRATION_TABLE(adc_12);

struct WntrVoltageCalibrationTable* hubble_adc_calibration_tables[] = {
    &adc_1_calibration_table,
    &adc_2_calibration_table,
    &adc_3_calibration_table,
    &adc_4_calibration_table,
    &adc_5_calibration_table,
    &adc_6_calibration_table,
    &adc_7_calibration_table,
    &adc_8_calibration_table,
    &adc_9_calibration_table,
    &adc_10_calibration_table,
    &adc_11_calibration_table,
    &adc_12_calibration_table,
};

/* Forward declarations */

void init_calibration_table(struct WntrVoltageCalibrationTable* table, size_t offset, bool load_from_nvm);

/* Public functions */

void hubble_calibration_tables_init(bool load_from_nvm) {
    for (size_t i = 0; i < WNTR_ARRAY_LEN(hubble_dac_calibration_tables); i++) {
        init_calibration_table(hubble_dac_calibration_tables[i], i, load_from_nvm);
    }
    for (size_t i = 0; i < WNTR_ARRAY_LEN(hubble_adc_calibration_tables); i++) {
        init_calibration_table(hubble_adc_calibration_tables[i], 16 + i, load_from_nvm);
    }
}

/* Private functions */

void init_calibration_table(struct WntrVoltageCalibrationTable* table, size_t index, bool load_from_nvm) {
    /* Initialize the table with the reference calibration. */
    memcpy(
        table->entries,
        dac_reference_calibration_entires_,
        sizeof(struct WntrVoltageCalibrationTableEntry) * table->len);
    /* Load the saved values (if available) */
    if (load_from_nvm) {
        HubbleVoltageCalibrationTable_load_from_nvm(*table, index);
    }
}
