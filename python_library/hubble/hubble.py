# Copyright (c) 2021 Alethea Katherine Flowers.
# Published under the standard MIT License.
# Full text available at: https://opensource.org/licenses/MIT

"""Python library for interacting with Hubble (our test platform)"""

import enum
import random
import struct
from wintertools import midi

from hubble.frontpanel import FrontPanel


class _IODescriptor:
    def __init__(self, type_, *args, **kwargs):
        self._name = None
        self._type = type_
        self._args = args
        self._kwargs = kwargs

    def __set_name__(self, owner, name):
        self._name = name

    def __set__(self, obj, value):
        raise AttributeError(f"Can not set property {self._name} on {obj}")

    def __get__(self, obj, objtype=None):
        cache_key = f"__{self._name}_cache"
        if cache_key not in obj.__dict__:
            obj.__dict__[cache_key] = self._type(obj, *self._args, **self._kwargs)
        return obj.__dict__[cache_key]


class DigitalIO:
    def __init__(self, device, pin):
        self._pin = pin
        self._name = None
        self._device = device

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
        self._voltage = 0
        self._value = 0

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value
        return self._device.set_dac(self._channel, self._mux, value)

    @property
    def voltage(self):
        return self._voltage

    @voltage.setter
    def voltage(self, voltage):
        self._voltage = voltage
        return self._device.set_dac_voltage(self._channel, self._mux, voltage)


class VoltageIn:
    def __init__(self, device, channel, mux):
        self._device = device
        self._channel = channel
        self._mux = mux

    @property
    def value(self):
        return self._device.read_adc(self._channel, self._mux)

    @property
    def voltage(self):
        return self._device.read_adc_voltage(self._channel, self._mux)


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

    IO1 = _IODescriptor(DigitalIO, 0)
    IO2 = _IODescriptor(DigitalIO, 1)
    IO3 = _IODescriptor(DigitalIO, 2)
    IO4 = _IODescriptor(DigitalIO, 3)
    IO5 = _IODescriptor(DigitalIO, 4)
    IO6 = _IODescriptor(DigitalIO, 5)
    IO7 = _IODescriptor(DigitalIO, 6)
    IO8 = _IODescriptor(DigitalIO, 7)
    IO9 = _IODescriptor(DigitalIO, 8)
    A9 = _IODescriptor(AnalogIn, 8)
    IO10 = _IODescriptor(DigitalIO, 9)
    A10 = _IODescriptor(AnalogIn, 9)
    IO11 = _IODescriptor(DigitalIO, 10)
    A11 = _IODescriptor(AnalogIn, 10)
    IO12 = _IODescriptor(DigitalIO, 11)
    A12 = _IODescriptor(AnalogIn, 11)
    IO13 = _IODescriptor(DigitalIO, 12)
    A13 = _IODescriptor(AnalogIn, 12)
    IO14 = _IODescriptor(DigitalIO, 13)
    A14 = _IODescriptor(AnalogIn, 13)
    IO15 = _IODescriptor(DigitalIO, 14)
    A15 = _IODescriptor(AnalogIn, 14)
    IO16 = _IODescriptor(DigitalIO, 15)
    A16 = _IODescriptor(AnalogIn, 15)
    IO17 = _IODescriptor(DigitalIO, 16)
    A17 = _IODescriptor(AnalogIn, 16)
    IO18 = _IODescriptor(DigitalIO, 17)
    A18 = _IODescriptor(AnalogIn, 17)
    IO19 = _IODescriptor(DigitalIO, 18)
    A19 = _IODescriptor(AnalogIn, 18)
    IO20 = _IODescriptor(DigitalIO, 19)
    A20 = _IODescriptor(AnalogIn, 19)
    IO21 = _IODescriptor(DigitalIO, 20)
    A21 = _IODescriptor(AnalogIn, 20)
    IO22 = _IODescriptor(DigitalIO, 21)
    IO23 = _IODescriptor(DigitalIO, 22)
    LED = _IODescriptor(DigitalIO, 22)

    VIN1A = _IODescriptor(VoltageIn, 0, 0)
    VIN1B = _IODescriptor(VoltageIn, 0, 1)
    VIN1C = _IODescriptor(VoltageIn, 0, 2)
    VIN1D = _IODescriptor(VoltageIn, 0, 3)
    VIN2A = _IODescriptor(VoltageIn, 1, 0)
    VIN2B = _IODescriptor(VoltageIn, 1, 1)
    VIN2C = _IODescriptor(VoltageIn, 1, 2)
    VIN2D = _IODescriptor(VoltageIn, 1, 3)
    VIN3A = _IODescriptor(VoltageIn, 2, 0)
    VIN3B = _IODescriptor(VoltageIn, 2, 1)
    VIN3C = _IODescriptor(VoltageIn, 2, 2)
    VIN3D = _IODescriptor(VoltageIn, 2, 3)
    VIN4A = _IODescriptor(VoltageIn, 3, 0)
    VIN4B = _IODescriptor(VoltageIn, 3, 1)
    VIN4C = _IODescriptor(VoltageIn, 3, 2)
    VIN4D = _IODescriptor(VoltageIn, 3, 3)

    VOUT1A = _IODescriptor(VoltageOut, 0, 0)
    VOUT1B = _IODescriptor(VoltageOut, 0, 1)
    VOUT1C = _IODescriptor(VoltageOut, 0, 2)
    VOUT1D = _IODescriptor(VoltageOut, 0, 3)
    VOUT2A = _IODescriptor(VoltageOut, 3, 0)
    VOUT2B = _IODescriptor(VoltageOut, 3, 1)
    VOUT2C = _IODescriptor(VoltageOut, 3, 2)
    VOUT2D = _IODescriptor(VoltageOut, 3, 3)
    VOUT3A = _IODescriptor(VoltageOut, 2, 0)
    VOUT3B = _IODescriptor(VoltageOut, 2, 1)
    VOUT3C = _IODescriptor(VoltageOut, 2, 2)
    VOUT3D = _IODescriptor(VoltageOut, 2, 3)
    VOUT4A = _IODescriptor(VoltageOut, 1, 0)
    VOUT4B = _IODescriptor(VoltageOut, 1, 1)
    VOUT4C = _IODescriptor(VoltageOut, 1, 2)
    VOUT4D = _IODescriptor(VoltageOut, 1, 3)
    RED_LED = property(lambda self: self._front_panel.RED_LED)
    BLUE_LED = property(lambda self: self._front_panel.BLUE_LED)
    GREEN_LED = property(lambda self: self._front_panel.GREEN_LED)

    def __init__(self):
        super().__init__()
        self._front_panel = FrontPanel()

    def get_firmware_version(self):
        resp = self.sysex(_SysExCommands.HELLO, response=True)
        self.version = bytearray(resp[3:-1]).decode("ascii")
        return self.version

    def reset(self):
        self.sysex(_SysExCommands.RESET)

    def read_gpio(self, pin):
        resp = self.sysex(_SysExCommands.READ_GPIO, data=[pin], response=True)
        return True if resp[3] else False

    def set_gpio(self, pin, value):
        self.sysex(
            _SysExCommands.SET_GPIO, data=[pin, 1 if value else 0], response=True
        )
        return

    def read_adc(self, channel, mux):
        resp = self.sysex(
            _SysExCommands.READ_ADC, data=[channel, mux], response=True, decode=True
        )
        (val,) = struct.unpack(">H", resp)
        return val

    def read_adc_voltage(self, channel, mux):
        resp = self.sysex(
            _SysExCommands.READ_ADC_VOLTAGE,
            data=[channel, mux],
            response=True,
            decode=True,
        )
        (val,) = struct.unpack(">f", resp)
        return val

    def scan_adc(self):
        return [self.read_adc(channel, mux) for channel in range(4) for mux in range(4)]

    def scan_adc_volts(self):
        return [
            self.read_adc_voltage(channel, mux)
            for channel in range(4)
            for mux in range(4)
        ]

    def set_dac(self, channel, mux, value):
        data = struct.pack(">BBH", channel, mux, value)
        self.sysex(_SysExCommands.SET_DAC, data=data, encode=True, response=True)

    def set_dac_voltage(self, channel, mux, value):
        data = struct.pack(">BBf", channel, mux, value)
        self.sysex(
            _SysExCommands.SET_DAC_VOLTAGE, data=data, encode=True, response=True
        )

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

    def start(self):
        self.BLUE_LED.on()
        self._front_panel.text = "Started..."

    def fail(self):
        self.RED_LED.flash()
        self.BLUE_LED.off()
        self.GREEN_LED.off()
        self._front_panel.oh_no()

    def print(self, msg=""):
        self._front_panel.text = msg

    def success(self):
        self.RED_LED.off()
        self.GREEN_LED.on()
        self._front_panel.text = random.choice(
            [
                "GOOD!",
                "NICE!",
                "GREAT!",
                "JAMMIN!",
                "COOL!",
                "RADICAL!",
                "TIGHT!",
                "AWESOME!",
                "EXTREME!",
                "PERFECT!!!",
            ]
        )
