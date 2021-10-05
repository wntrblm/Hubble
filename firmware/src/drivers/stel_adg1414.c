/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "stel_adg1414.h"
#include "stel_config.h"
#include "wntr_assert.h"

/* Static variables. */
static const struct StelSERCOMSPI* spi_;

/* Public functions */

void stel_adg1414_init(const struct StelSERCOMSPI* spi) {
    spi_ = spi;
    WntrGPIOPin_set_as_output(STEL_ADG1414_CS);
}

void stel_adg1414_write(const uint8_t data[], size_t count) {
    WntrGPIOPin_set(STEL_ADG1414_CS, false);
    stel_sercom_spi_write(spi_, data, count);
    WntrGPIOPin_set(STEL_ADG1414_CS, true);
}

void stel_adg1414_write_switches(const bool data[], const size_t count) {
    WNTR_ASSERT_DEBUG(count % 8 == 0);
    WntrGPIOPin_set(STEL_ADG1414_CS, false);
    for (size_t i = 0; i < count; i += 8) {
        const uint8_t data_byte =
            ((data[i] & 0x1) << 7 | (data[i + 1] & 0x1) << 6 | (data[i + 2] & 0x1) << 5 | (data[i + 3] & 0x1) << 4 |
             (data[i + 4] & 0x1) << 3 | (data[i + 5] & 0x1) << 2 | (data[i + 6] & 0x1) << 1 | (data[i + 7] & 0x1));
        stel_sercom_spi_write(spi_, &data_byte, 1);
    }
    WntrGPIOPin_set(STEL_ADG1414_CS, true);
}
