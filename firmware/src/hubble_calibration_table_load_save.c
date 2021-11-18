/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "hubble_calibration_table_load_save.h"
#include "hubble_data_converter_helpers.h"
#include "hubble_nvm.h"
#include "printf.h"
#include "wntr_assert.h"
#include "wntr_pack.h"
#include <stdbool.h>
#include <string.h>

/*
    Routines for loading/saving the ADC/DAC calibration tables to NVM
*/

extern uint8_t _nvm_addr;
extern uint8_t _nvm_length;

static uint8_t nvm_buf_[256];
static const size_t nvm_buf_len_ = sizeof(nvm_buf_) / sizeof(nvm_buf_len_);
static const size_t entry_size_ = sizeof(struct HubbleVoltageCalibrationTableEntry);

/* There are 32 banks of 256 bytes to work with */
#define VALID_BANK_MARKER 0xAB
#define BANK_MARKER_ADDR(buf, table_len) (buf + (table_len * entry_size_))
#define NVM_BANK_ADDR(bank_number) ((&_nvm_addr) + (bank_number * 0x100))

/* Public functions. */

bool hubble_load_voltage_calibration_table(
    struct HubbleVoltageCalibrationTableEntry* table, size_t table_len, uint8_t bank) {

    uint8_t* src = NVM_BANK_ADDR(bank);
    uint8_t* src_marker = BANK_MARKER_ADDR(src, table_len);

    if ((*src_marker) != VALID_BANK_MARKER) {
        printf("NVM bank %u does not have a valid calibration table.\n", bank);
        return false;
    }
    src++;

    for (size_t idx = 0; idx < table_len; idx++) {
        table[idx].measured = WNTR_UNPACK_FLOAT(src, idx * entry_size_);
        table[idx].expected = WNTR_UNPACK_FLOAT(src, idx * entry_size_ + 4);
    }

    printf("Loaded calibration table from NVM bank %u\n", bank);

    return true;
}

void hubble_save_voltage_calibration_table(
    struct HubbleVoltageCalibrationTableEntry* table, size_t table_len, uint8_t bank) {
    WNTR_ASSERT(table_len * sizeof(struct HubbleVoltageCalibrationTableEntry) <= sizeof(nvm_buf_));

    for (size_t idx = 0; idx < table_len; idx++) {
        struct HubbleVoltageCalibrationTableEntry entry = table[idx];
        WNTR_PACK_FLOAT(entry.expected, nvm_buf_, idx * entry_size_);
        WNTR_PACK_FLOAT(entry.measured, nvm_buf_, idx * entry_size_ + 4);
    }

    uint8_t* dst_marker = BANK_MARKER_ADDR(nvm_buf_, table_len);
    *dst_marker = VALID_BANK_MARKER;

    hubble_nvm_write(NVM_BANK_ADDR(bank), nvm_buf_, nvm_buf_len_);

    printf("Saved calibration table to NVM bank %u\n", bank);
}

void hubble_erase_calibration_table(uint32_t bank) {
    memset(nvm_buf_, 0xFF, nvm_buf_len_);

    hubble_nvm_write(NVM_BANK_ADDR(bank), nvm_buf_, nvm_buf_len_);

    printf("Erased calibration table in NVM bank %u\n", bank);
}
