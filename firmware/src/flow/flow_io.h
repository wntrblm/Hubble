/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include "currents.h"
#include "flow_nodes.h"
#include "wntr_midi.h"

struct FlowInputs {
    float a;
    float b;
    struct WntrMIDIMessage* midi_msg;
};

struct FlowOutputs {
    float one;
    float two;
    float three;
    float four;
    float delta;
    float gamma;
};

struct FlowStepContext {
    struct FlowNodeState* states;
    struct CurrentsFlow* flow;
    const struct FlowInputs* inputs;
    struct FlowOutputs* outputs;
};

extern struct FlowStepContext flow_step_context;
