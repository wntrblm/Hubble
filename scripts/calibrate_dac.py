import time

import pyvisa

from wintertools import multimeter
from hubble import Hubble

DAC = 3

h = Hubble()
rm = pyvisa.ResourceManager("@py")
mm = multimeter.Multimeter(rm)

h.set_calibration_enabled(False)

for n, voltage in enumerate(range(-8, 9)):
    h.set_dac_voltage(DAC, 0, voltage)
    time.sleep(0.02)
    measured = mm.read_voltage()
    print(n, voltage, measured)
    h.set_calibration_table_entry(DAC, n, voltage, measured)

h.save_calibration_table(DAC)
h.set_calibration_enabled(True)

for voltage in range(-8, 9):
    h.set_dac_voltage(DAC, 0, voltage)
    measured = mm.read_voltage_fast()
    diff_mv = abs((voltage - measured) * 1000)
    print(f"Expected: {voltage:+.2f} Volts, Measured: {measured:+0.4f} Volts, Diff: {diff_mv:0.2f} mV")
