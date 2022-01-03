from wintertools import midi


def _midi_clamp(val):
    return min(127, max(0, int(val)))


class _LED:
    NORMAL = 0
    OFF = 1
    ON = 2
    FLASHING = 3
    BREATHING = 4

    def __init__(self, device, number):
        self._device = device
        self._number = number
        self._mode = self.NORMAL
        self._brightness = 0

    def update(self):
        self._device.send(
            0x90, (self.mode << 4) | (self._number), _midi_clamp(127 * self._brightness)
        )

    @property
    def brightness(self):
        return self._brightness

    @brightness.setter
    def brightness(self, value):
        self._brightness = value
        self._mode = self.NORMAL
        self.update()

    @property
    def mode(self):
        return self._mode

    @mode.setter
    def mode(self, value):
        self._mode = value
        self.update()

    def flash(self):
        self.mode = self.FLASHING

    def breathe(self):
        self.mode = self.BREATHING

    def off(self):
        self.mode = self.OFF

    def on(self):
        self.mode = self.ON


class FrontPanel(midi.MIDIDevice):
    # MIDI_PORT_NAME = "Feather RP2040 CircuitPython usb_midi.ports[0]"
    MIDI_PORT_NAME = "Pico CircuitPython usb_midi.ports[0]"
    SYSEX_MARKER = 0x77

    def __init__(self):
        super().__init__()
        self.BLUE_LED = _LED(self, 0)
        self.GREEN_LED = _LED(self, 1)
        self.RED_LED = _LED(self, 2)
        self.reset()

    def reset(self):
        self.BLUE_LED.breathe()
        self.GREEN_LED.off()
        self.RED_LED.off()
        self.text = "Connected"

    @property
    def text(self):
        return ""

    @text.setter
    def text(self, value):
        self.sysex(0x01, data=value.encode("ascii"))

    def oh_no(self):
        self.sysex(0x02)
