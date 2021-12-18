import time

import adafruit_displayio_sh1107
import board
import digitalio
import displayio
import pwmio
import rotaryio
import terminalio
import usb_hid
import usb_midi
from adafruit_display_text import bitmap_label
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.keycode import Keycode
import adafruit_imageload

import smolmidi

# Buttons and bows


class Button:
    def __init__(self, pin):
        self.io = digitalio.DigitalInOut(pin)
        self.io.switch_to_input(pull=digitalio.Pull.UP)
        self.last_value = self.io.value
        self.current_value = self.last_value

    def update(self):
        self.last_value = self.current_value
        self.current_value = self.io.value

    @property
    def value(self):
        return self.current_value

    @property
    def pressed(self):
        return self.last_value is True and self.current_value is False

    @property
    def released(self):
        return self.last_value is False and self.current_value is True


class KeyboardButton:
    def __init__(self, button, value):
        self.button = button
        self.value = value

    def update(self):
        if self.button.pressed:
            if isinstance(self.value, str):
                KEYBOARD_LAYOUT.write(self.value)
            elif isinstance(self.value, tuple):
                KEYBOARD.send(*self.value)
            else:
                KEYBOARD.send(self.value)


class Encoder:
    def __init__(self, pin_1, pin_2, reverse=False):
        self.io = rotaryio.IncrementalEncoder(pin_1, pin_2)
        self.reverse = reverse
        self.last_position = 0
        self.current_position = 0

    def update(self):
        self.last_position = self.current_position

        if not self.reverse:
            self.current_position = self.io.position
        else:
            self.current_position = -self.io.position

    @property
    def position(self):
        return self.current_position

    @property
    def delta(self):
        return self.current_position - self.last_position

    @property
    def increased(self):
        return self.last_position < self.current_position

    @property
    def decreased(self):
        return self.last_position > self.current_position


class LED:
    NORMAL = 0
    OFF = 1
    ON = 2
    FLASHING = 3
    BREATHING = 4

    def __init__(self, pin):
        self.io = pwmio.PWMOut(pin)
        self.mode = self.NORMAL
        self.brightness = 0

    @property
    def brightness(self):
        return 0

    @brightness.setter
    def brightness(self, val):
        self.io.duty_cycle = min(65535, max(int(65535 * val), 0))

    def update(self):
        if self.mode == self.NORMAL:
            pass
        elif self.mode == self.OFF:
            self.brightness = 0
        elif self.mode == self.ON:
            self.brightness = 1
        elif self.mode == self.FLASHING:
            self.brightness = (time.monotonic() * 4) % 1.0
        elif self.mode == self.BREATHING:
            self.brightness = abs(-1 + ((time.monotonic() / 2) % 1.0) * 2)


def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i : i + n]


# Keyboard, gamepad and such

KEYBOARD = Keyboard(usb_hid.devices)
KEYBOARD_LAYOUT = KeyboardLayoutUS(KEYBOARD)

# I/O

ENCODER = Encoder(board.D9, board.D10, reverse=True)

GREEN_BTN_1 = Button(board.TX)
GREEN_BTN_1_KB = KeyboardButton(GREEN_BTN_1, "python3 factory_setup.py\n")
GREEN_BTN_2 = Button(board.D12)
GREEN_BTN_2_KB = KeyboardButton(GREEN_BTN_2, Keycode.ENTER)
RED_BTN = Button(board.D11)
RED_BTN_KB = KeyboardButton(RED_BTN, (Keycode.CONTROL, Keycode.C))
ENCODER_BTN = Button(board.D4)
ENCODER_BTN_KB = KeyboardButton(ENCODER_BTN, Keycode.KEYPAD_ENTER)
SECOND_SWITCH = Button(board.RX)
SECOND_SWITCH_KB = KeyboardButton(SECOND_SWITCH, Keycode.SPACE)
POWER_SWITCH = Button(board.MISO)

BLUE_LED = LED(board.D13)
GREEN_LED = LED(board.D6)
RED_LED = LED(board.D5)

# MIDI

midi_in = smolmidi.MidiIn(usb_midi.ports[0])

# Display
I2C = board.I2C()
displayio.release_displays()
display_bus = displayio.I2CDisplay(I2C, device_address=0x3C)
display = adafruit_displayio_sh1107.SH1107(
    display_bus, width=128, height=64, rotation=0
)
display.auto_refresh = True
display_group = displayio.Group()
display.show(display_group)

text = bitmap_label.Label(
    terminalio.FONT, text="Idle", scale=2, color=0xFFFFFF, x=0, y=10
)
display_group.append(text)

oh_no_bitmap, oh_no_palette = adafruit_imageload.load(
    "/ohno.bmp", bitmap=displayio.Bitmap, palette=displayio.Palette
)
oh_no_tile_grid = displayio.TileGrid(oh_no_bitmap, pixel_shader=oh_no_palette)
oh_no_tile_grid.hidden = True

# Now the fun stuff.
RED_LED.mode = LED.BREATHING

while True:
    POWER_SWITCH.update()
    ENCODER.update()
    GREEN_BTN_1.update()
    GREEN_BTN_1_KB.update()
    GREEN_BTN_2.update()
    GREEN_BTN_2_KB.update()
    RED_BTN.update()
    RED_BTN_KB.update()
    ENCODER_BTN.update()
    ENCODER_BTN_KB.update()
    SECOND_SWITCH.update()
    SECOND_SWITCH_KB.update()

    if ENCODER.increased:
        for _ in range(ENCODER.delta):
            KEYBOARD.send(Keycode.RIGHT_ARROW)
    elif ENCODER.decreased:
        for _ in range(abs(ENCODER.delta)):
            KEYBOARD.send(Keycode.LEFT_ARROW)

    if POWER_SWITCH.pressed:
        text.text = "Ready!"
    elif POWER_SWITCH.released:
        GREEN_LED.mode = GREEN_LED.OFF
        RED_LED.mode = GREEN_LED.OFF
        text.text = "Idle"

    BLUE_LED.update()
    GREEN_LED.update()
    RED_LED.update()

    msg = midi_in.receive()
    if msg:
        if msg.type == smolmidi.NOTE_ON:
            led_num = msg.data[0] & 0x0F
            led_mode = (msg.data[0] & 0xF0) >> 4

            if led_num == 0:
                led = BLUE_LED
            elif led_num == 1:
                led = GREEN_LED
            else:
                led = RED_LED

            led.brightness = msg.data[1] / 127
            led.mode = led_mode

        if msg.type == smolmidi.SYSEX:
            data, _ = midi_in.receive_sysex(128)
            if not data:
                continue

            command = data[1]

            if command == 0x01:
                new_text = bytes(data[2:]).decode("ascii")
                lines = "\n".join(line.strip() for line in chunks(new_text, 10))
                text.text = lines
                if not oh_no_tile_grid.hidden:
                    oh_no_tile_grid.hidden = True
                    display_group.pop()

            elif command == 0x02:
                oh_no_tile_grid.hidden = False
                display_group.append(oh_no_tile_grid)
