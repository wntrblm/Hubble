/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "flow_nodes.h"
#include "flow_io.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define GET_STATE(type, property) struct type* state = &flow_step_context.states[node->id].property;

CURRENTS_NODE_FN(none) {}

CURRENTS_NODE_FN(tick) { CURRENTS_SEND(0, {}); }

CURRENTS_NODE_FN(input_a) { CURRENTS_SEND(0, {.f = flow_step_context.inputs->a}); }

CURRENTS_NODE_FN(input_b) { CURRENTS_SEND(0, {.f = flow_step_context.inputs->b}); }

CURRENTS_NODE_FN(output_one) { flow_step_context.outputs->one = data.f; }

CURRENTS_NODE_FN(output_two) { flow_step_context.outputs->two = data.f; }

CURRENTS_NODE_FN(output_three) { flow_step_context.outputs->three = data.f; }

CURRENTS_NODE_FN(output_four) { flow_step_context.outputs->four = data.f; }

CURRENTS_NODE_FN(output_delta) { flow_step_context.outputs->delta = data.f; }

CURRENTS_NODE_FN(output_gamma) { flow_step_context.outputs->gamma = data.f; }

CURRENTS_NODE_FN(multiply) {
    GET_STATE(MultiplyState, multiply);
    CURRENTS_SEND(0, {.f = data.f * state->by});
}

CURRENTS_NODE_FN(midi_in) {
    if (flow_step_context.inputs->midi_msg == NULL) {
        return;
    }

    CURRENTS_SEND(0, {.v = (void*)flow_step_context.inputs->midi_msg});
}

static float note_to_v_oct(uint8_t note) {
    if (note < 24) {
        return 0.f;
    }

    return (note - 24) * (1.f / 12.f);
}

CURRENTS_NODE_FN(midi_to_cv) {
    struct WntrMIDIMessage* msg = data.v;
    if (wntr_midi_get_type(msg) != MIDI_CHANNEL_NOTE_ON) {
        return;
    }

    /* Velocity zero is the same as note off, so ignore it */
    if (msg->data_1 == 0) {
        return;
    }

    float cv = note_to_v_oct(msg->data_0);
    float velocity = msg->data_1 / 127.0f;

    CURRENTS_SEND(0, {.f = cv});
    CURRENTS_SEND(1, {.f = velocity});
}

CURRENTS_NODE_FN(midi_to_gate) {
    GET_STATE(MIDIToGateState, midi_to_gate);
    const struct WntrMIDIMessage* msg = data.v;

    if (msg == NULL) {
        return;
    }
    switch (wntr_midi_get_type(msg)) {
        case MIDI_CHANNEL_NOTE_ON:
            /* Note on with velocity 0 is note off. */
            if (msg->data_1 == 0) {
                goto note_off;
            }

            state->current_note = msg->data_0;
            CURRENTS_SEND(0, {.f = 5.0f});
            break;

        case MIDI_CHANNEL_NOTE_OFF:
        note_off:
            if (msg->data_0 == state->current_note) {
                CURRENTS_SEND(0, {.f = 0.0f});
            }

            break;

        default:
            break;
    }
}

CURRENTS_NODE_FN(midi_cc) {
    GET_STATE(MIDICCState, midi_cc);
    const struct WntrMIDIMessage* msg = data.v;

    if (wntr_midi_get_type(msg) != MIDI_CHANNEL_CONTROLLER_CHANGE) {
        return;
    }

    if (msg->data_0 != state->number) {
        return;
    }

    float cc = msg->data_1 / 127.0f;

    CURRENTS_SEND(0, {.f = cc});
}
