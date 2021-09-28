/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "flow_runner.h"
#include "currents.h"
#include "flow_io.h"
#include "flow_nodes.h"
#include "generated_flow.h"
#include "wntr_midi.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define ARRAY_SIZE(var) ((sizeof var) / (sizeof var[0]))

static struct {
    struct CurrentsNode nodes[64];
    struct FlowNodeState states[64];
    struct CurrentsLink links[128];
    struct CurrentsEvent events[128];
} storage;

static struct CurrentsFlow flow = {
    .nodes = storage.nodes,
    .nodes_capacity = ARRAY_SIZE(storage.nodes),
    .links = storage.links,
    .links_capacity = ARRAY_SIZE(storage.links),
    .events = storage.events,
    .events_capacity = ARRAY_SIZE(storage.events),
};

void flow_runner_init() {
    CurrentsFlow_init(&flow);
    flow_step_context.flow = &flow;
    flow_step_context.states = storage.states;

    /* Wire up the generated flow program. */
    generated_flow_init(&flow, storage.states);

    /* Mark certain nodes as stepped. */
    for (size_t i = 0; i < flow.nodes_capacity; i++) {
        if (flow.nodes[i].fn == midi_in_fn || flow.nodes[i].fn == input_a_fn || flow.nodes[i].fn == input_b_fn) {
            flow.nodes[i].on_step = true;
        }
    }

    CurrentsFlow_start(&flow);
}

void flow_runner_step(const struct FlowInputs* inputs, struct FlowOutputs* outputs) {
    flow_step_context.inputs = inputs;
    flow_step_context.outputs = outputs;
    CurrentsFlow_step(&flow);
}
