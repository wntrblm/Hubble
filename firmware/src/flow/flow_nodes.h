/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include "currents.h"
#include <stdint.h>

struct FlowNodeState {
    union {
        struct MIDIInState {
            uint8_t channel;
        } midi_in;
        struct MIDIToGateState {
            uint8_t current_note;
        } midi_to_gate;
        struct MIDICCState {
            uint8_t number;
        } midi_cc;
        struct MultiplyState {
            float by;
        } multiply;
    };
};

CURRENTS_NODE_FN(none);
CURRENTS_NODE_FN(input_a);
CURRENTS_NODE_FN(input_b);
CURRENTS_NODE_FN(output_one);
CURRENTS_NODE_FN(output_two);
CURRENTS_NODE_FN(output_three);
CURRENTS_NODE_FN(output_four);
CURRENTS_NODE_FN(output_delta);
CURRENTS_NODE_FN(output_gamma);
CURRENTS_NODE_FN(multiply);
CURRENTS_NODE_FN(midi_in);
CURRENTS_NODE_FN(midi_to_cv);
CURRENTS_NODE_FN(midi_to_gate);
CURRENTS_NODE_FN(midi_cc);
