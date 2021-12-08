# Copyright (c) 2021 Alethea Katherine Flowers.
# Published under the standard MIT License.
# Full text available at: https://opensource.org/licenses/MIT

import time

from hubble import Hubble

ADC = 3

h = Hubble()

h.set_calibration_enabled(False)

for n, voltage in enumerate(range(-8, 9)):
    h.set_calibration_enabled(True)
    h.set_dac_voltage(0, 0, voltage)
    time.sleep(0.02)
    h.set_calibration_enabled(False)
    measured = h.read_adc_voltage(ADC, 0)
    print(voltage, measured)
    h.set_calibration_table_entry(4 + ADC, n, voltage, measured)

h.save_calibration_table(4 + ADC)

h.set_calibration_enabled(True)
for voltage in range(-8, 9):
    h.set_dac_voltage(0, 0, voltage)
    measured = h.read_adc_voltage(ADC, 0)
    diff_mv = abs((voltage - measured) * 1000)
    print(f"Expected: {voltage:+.2f} Volts, Measured: {measured:+0.4f} Volts, Diff: {diff_mv:0.2f} mV")
