#pragma once

#include "stel_sercom_spi.h"

void stel_adg1414_init(const struct StelSERCOMSPI* spi);
void stel_adg1414_write(const uint8_t data[], size_t count);
void stel_adg1414_write_switches(const bool data[], const size_t count);
