/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "midi_backend.h"
#include "wntr_midi.h"
#include <stdio.h>

bool wntr_midi_receive(struct WntrMIDIMessage* msg) {
    uint8_t bytes[4];
    if (midi_backend_receive(bytes)) {
        msg->cable = 0;
        msg->code_index = (bytes[0] & 0xF0) >> 4;
        msg->status = bytes[0];
        msg->data_0 = bytes[1];
        msg->data_1 = bytes[2];

        printf("MIDI IN: 0x%02x 0x%02x 0x%02x 0x%02x\n", msg->code_index, msg->status, msg->data_0, msg->data_1);

        return true;
    }
    return false;
}
