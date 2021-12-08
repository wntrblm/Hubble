# Copyright (c) 2021 Alethea Katherine Flowers.
# Published under the standard MIT License.
# Full text available at: https://opensource.org/licenses/MIT

"""Control Hubble (our test platform)"""

__version__ = "0.0.0a0"

import enum
import struct

from wintertools import midi


class DigitalIO:
    def __init__(self, device, pin):
        self._device = device
        self._pin = pin

    @property
    def value(self):
        return self._device.read_gpio(self._pin)

    @value.setter
    def value(self, value):
        self._device.set_gpio(self._pin, value)


class AnalogIn:
    def __init__(self, device, pin):
        self._device = device
        self._pin = pin

    @property
    def value(self):
        return self._device.read_gpio_adc(self._pin)


class VoltageOut:
    def __init__(self, device, channel, mux):
        self._device = device
        self._channel = channel
        self._mux = mux

    def value(self, value):
        return self._device.set_dac(self._channel, self._mux, value)

    value = property(None, value)

    def voltage(self, voltage):
        return self._device.set_dac_voltage(
            self._channel, self._mux, voltage
        )

    voltage = property(None, voltage)


class VoltageIn:
    def __init__(self, device, channel, mux):
        self._device = device
        self._channel = channel
        self._mux = mux

    @property
    def value(self):
        return self._device.read_adc(self._device, self._channel, self._mux)

    @property
    def voltage(self):
        return self._device.read_adc_voltage(self._device, self._channel, self._mux)


class _SysExCommands(enum.IntEnum):
    HELLO = 0x01
    RESET = 0x02
    READ_GPIO = 0x03
    SET_GPIO = 0x04
    READ_ADC = 0x05
    READ_ADC_VOLTAGE = 0x06
    SET_DAC = 0x07
    SET_DAC_VOLTAGE = 0x08
    SET_CALIBATION_ENABLED = 0x50
    SET_CALIBRATION_TABLE_ENTRY = 0x51
    SAVE_CALIBRATION_TABLE = 0x52


class _DACChannels(enum.IntEnum):
    D1 = 0
    D2 = 3
    D3 = 2
    D4 = 1

class _DACMUX(enum.IntEnum):


    MUX_A = 0
    MUX_B = 1
    MUX_C = 2
    MUX_D = 3


class Hubble(midi.MIDIDevice):
    MIDI_PORT_NAME = "Hubble"
    SYSEX_MARKER = 0x77

    def __init__(self):
        super().__init__()

        self.IO1 = DigitalIO(self, 0)
        self.IO2 = DigitalIO(self, 1)
        self.IO3 = DigitalIO(self, 2)
        self.IO4 = DigitalIO(self, 3)
        self.IO5 = DigitalIO(self, 4)
        self.IO6 = DigitalIO(self, 5)
        self.IO7 = DigitalIO(self, 6)
        self.IO8 = DigitalIO(self, 7)
        self.IO9 = DigitalIO(self, 8)
        self.A9 = AnalogIn(self, 8)
        self.IO10 = DigitalIO(self, 9)
        self.A10 = AnalogIn(self, 9)
        self.IO11 = DigitalIO(self, 10)
        self.A11 = AnalogIn(self, 10)
        self.IO12 = DigitalIO(self, 11)
        self.A12 = AnalogIn(self, 11)
        self.IO13 = DigitalIO(self, 12)
        self.A13 = AnalogIn(self, 12)
        self.IO14 = DigitalIO(self, 13)
        self.A14 = AnalogIn(self, 13)
        self.IO15 = DigitalIO(self, 14)
        self.A15 = AnalogIn(self, 14)
        self.IO16 = DigitalIO(self, 15)
        self.A16 = AnalogIn(self, 15)
        self.IO17 = DigitalIO(self, 16)
        self.A17 = AnalogIn(self, 16)
        self.IO18 = DigitalIO(self, 17)
        self.A18 = AnalogIn(self, 17)
        self.IO19 = DigitalIO(self, 18)
        self.A19 = AnalogIn(self, 18)
        self.IO20 = DigitalIO(self, 19)
        self.A20 = AnalogIn(self, 19)
        self.IO21 = DigitalIO(self, 20)
        self.A21 = AnalogIn(self, 20)
        self.IO22 = DigitalIO(self, 21)
        self.IO23 = DigitalIO(self, 22)
        self.LED = self.IO23

        self.VIN1A = VoltageIn(self, 0, 0)
        self.VIN1B = VoltageIn(self, 0, 1)
        self.VIN1C = VoltageIn(self, 0, 2)
        self.VIN1D = VoltageIn(self, 0, 3)
        self.VIN2A = VoltageIn(self, 1, 0)
        self.VIN2B = VoltageIn(self, 1, 1)
        self.VIN2C = VoltageIn(self, 1, 2)
        self.VIN2D = VoltageIn(self, 1, 3)
        self.VIN3A = VoltageIn(self, 2, 0)
        self.VIN3B = VoltageIn(self, 2, 1)
        self.VIN3C = VoltageIn(self, 2, 2)
        self.VIN3D = VoltageIn(self, 2, 3)
        self.VIN4A = VoltageIn(self, 3, 0)
        self.VIN4B = VoltageIn(self, 3, 1)
        self.VIN4C = VoltageIn(self, 3, 2)
        self.VIN4D = VoltageIn(self, 3, 3)

        self.VOUT1A = VoltageOut(self, 0, 0)
        self.VOUT1B = VoltageOut(self, 0, 1)
        self.VOUT1C = VoltageOut(self, 0, 2)
        self.VOUT1D = VoltageOut(self, 0, 3)
        self.VOUT2A = VoltageOut(self, 3, 0)
        self.VOUT2B = VoltageOut(self, 3, 1)
        self.VOUT2C = VoltageOut(self, 3, 2)
        self.VOUT2D = VoltageOut(self, 3, 3)
        self.VOUT3A = VoltageOut(self, 2, 0)
        self.VOUT3B = VoltageOut(self, 2, 1)
        self.VOUT3C = VoltageOut(self, 2, 2)
        self.VOUT3D = VoltageOut(self, 2, 3)
        self.VOUT4A = VoltageOut(self, 1, 0)
        self.VOUT4B = VoltageOut(self, 1, 1)
        self.VOUT4C = VoltageOut(self, 1, 2)
        self.VOUT4D = VoltageOut(self, 1, 3)

    def get_firmware_version(self):
        resp = self.sysex(_SysExCommands.HELLO, response=True)
        self.version = bytearray(resp[3:-1]).decode("ascii")
        return self.version

    def reset(self):
        self.sysex(_SysExCommands.RESET)

    def read_gpio(self, pin):
        resp = self.sysex(_SysExCommands.READ_GPIO, data=[pin], response=True)
        print(resp)
        return True if resp[4] else False

    def set_gpio(self, pin, value):
        self.sysex(_SysExCommands.SET_GPIO, data=[pin, 1 if value else 0], response=True)
        return

    def read_adc(self, channel, mux):
        resp = self.sysex(
            _SysExCommands.READ_ADC, data=[channel, mux], response=True, decode=True
        )
        (val,) = struct.unpack(">H", resp)
        return val

    def read_adc_voltage(self, channel, mux):
        resp = self.sysex(
            _SysExCommands.READ_ADC_VOLTAGE, data=[channel, mux], response=True, decode=True
        )
        (val,) = struct.unpack(">f", resp)
        return val

    def scan_adc(self):
        return [self.read_adc(channel, mux) for channel in range(4) for mux in range(4)]

    def scan_adc_volts(self):
        return [self.read_adc_voltage(channel, mux) for channel in range(4) for mux in range(4)]

    def set_dac(self, channel, mux, value):
        data = struct.pack(">BBH", channel, mux, value)
        self.sysex(_SysExCommands.SET_DAC, data=data, encode=True, response=True)

    def set_dac_voltage(self, channel, mux, value):
        data = struct.pack(">BBf", channel, mux, value)
        self.sysex(_SysExCommands.SET_DAC_VOLTAGE, data=data, encode=True, response=True)

    def set_calibration_enabled(self, enabled):
        self.sysex(
            _SysExCommands.SET_CALIBATION_ENABLED,
            data=[1 if enabled else 0],
            response=True,
        )

    def set_calibration_table_entry(self, table, index, expected, measured):
        data = struct.pack(">BBff", table, index, expected, measured)
        self.sysex(
            _SysExCommands.SET_CALIBRATION_TABLE_ENTRY,
            data=data,
            encode=True,
            response=True,
        )

    def save_calibration_table(self, table):
        self.sysex(_SysExCommands.SAVE_CALIBRATION_TABLE, data=[table], response=True)
