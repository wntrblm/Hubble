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
    def __init__(self, device, channel):
        self._device = device
        self._channel = channel
        self._voltage = 0
        self._value = 0

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value
        return self._device.set_dac(self._channel, value)

    @property
    def voltage(self):
        return self._voltage

    @voltage.setter
    def voltage(self, voltage):
        self._voltage = voltage
        return self._device.set_dac_voltage(self._channel, voltage)


class VoltageIn:
    def __init__(self, device, channel):
        self._device = device
        self._channel = channel

    @property
    def value(self):
        return self._device.read_adc(self._channel)

    @property
    def voltage(self):
        return self._device.read_adc_voltage(self._channel)


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
    IO10 = _IODescriptor(DigitalIO, 9)
    IO11 = _IODescriptor(DigitalIO, 10)
    IO12 = _IODescriptor(DigitalIO, 11)
    IO13 = _IODescriptor(DigitalIO, 12)
    IO14 = _IODescriptor(DigitalIO, 13)
    IO15 = _IODescriptor(DigitalIO, 14)
    IO16 = _IODescriptor(DigitalIO, 15)
    IO17 = _IODescriptor(DigitalIO, 16)
    IO18 = _IODescriptor(DigitalIO, 17)
    IO19 = _IODescriptor(DigitalIO, 18)
    IO20 = _IODescriptor(DigitalIO, 19)
    IO21 = _IODescriptor(DigitalIO, 20)
    IO22 = _IODescriptor(DigitalIO, 21)
    IO23 = _IODescriptor(DigitalIO, 22)

    SER1_0 = _IODescriptor(DigitalIO, 23)
    SER1_1 = _IODescriptor(DigitalIO, 24)
    SER1_2 = _IODescriptor(DigitalIO, 25)
    SER1_3 = _IODescriptor(DigitalIO, 26)
    SER2_0 = _IODescriptor(DigitalIO, 27)
    SER2_1 = _IODescriptor(DigitalIO, 28)
    SER2_2 = _IODescriptor(DigitalIO, 29)
    SER2_3 = _IODescriptor(DigitalIO, 30)

    LED = _IODescriptor(DigitalIO, 31)
    DS_POWER = _IODescriptor(DigitalIO, 32)

    VIN1 = _IODescriptor(VoltageIn, 0)
    VIN2 = _IODescriptor(VoltageIn, 1)
    VIN3 = _IODescriptor(VoltageIn, 2)
    VIN4 = _IODescriptor(VoltageIn, 3)
    VIN5 = _IODescriptor(VoltageIn, 4)
    VIN6 = _IODescriptor(VoltageIn, 5)
    VIN7 = _IODescriptor(VoltageIn, 6)
    VIN8 = _IODescriptor(VoltageIn, 7)
    VIN9 = _IODescriptor(VoltageIn, 8)
    VIN10 = _IODescriptor(VoltageIn, 9)
    VIN11 = _IODescriptor(VoltageIn, 10)
    VIN12 = _IODescriptor(VoltageIn, 11)
    AIN1 = _IODescriptor(VoltageIn, 12)
    AIN2 = _IODescriptor(VoltageIn, 13)
    AIN3 = _IODescriptor(VoltageIn, 14)
    AIN4 = _IODescriptor(VoltageIn, 15)

    VOUT1 = _IODescriptor(VoltageOut, 0)
    VOUT2 = _IODescriptor(VoltageOut, 1)
    VOUT3 = _IODescriptor(VoltageOut, 2)
    VOUT4 = _IODescriptor(VoltageOut, 3)
    VOUT5 = _IODescriptor(VoltageOut, 4)
    VOUT6 = _IODescriptor(VoltageOut, 5)
    VOUT7 = _IODescriptor(VoltageOut, 6)
    VOUT8 = _IODescriptor(VoltageOut, 7)
    VOUT9 = _IODescriptor(VoltageOut, 8)
    VOUT10 = _IODescriptor(VoltageOut,9 )
    VOUT11 = _IODescriptor(VoltageOut, 10)
    VOUT12 = _IODescriptor(VoltageOut, 11)
    AOUT1 = _IODescriptor(VoltageOut, 12)
    AOUT2 = _IODescriptor(VoltageOut, 13)
    AOUT3 = _IODescriptor(VoltageOut, 14)
    AOUT4 = _IODescriptor(VoltageOut, 15)

    RED_LED = property(lambda self: self._front_panel.RED_LED)
    BLUE_LED = property(lambda self: self._front_panel.BLUE_LED)
    GREEN_LED = property(lambda self: self._front_panel.GREEN_LED)

    def __init__(self):
        super().__init__()
        # self._front_panel = FrontPanel()

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

    def read_adc(self, channel):
        resp = self.sysex(
            _SysExCommands.READ_ADC, data=[channel], response=True, decode=True
        )
        (val,) = struct.unpack(">H", resp)
        return val

    def read_adc_voltage(self, channel):
        resp = self.sysex(
            _SysExCommands.READ_ADC_VOLTAGE,
            data=[channel],
            response=True,
            decode=True,
        )
        (val,) = struct.unpack(">f", resp)
        return val

    def scan_adc(self):
        return [self.read_adc(channel) for channel in range(16)]

    def scan_adc_volts(self):
        return [
            self.read_adc_voltage(channel)
            for channel in range(16)
        ]

    def set_dac(self, channel, value):
        data = struct.pack(">BH", channel, value)
        self.sysex(_SysExCommands.SET_DAC, data=data, encode=True, response=True)

    def set_dac_voltage(self, channel, value):
        data = struct.pack(">Bf", channel, value)
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
