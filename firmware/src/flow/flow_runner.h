/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#pragma once

#include "currents.h"
#include "flow_io.h"

void flow_runner_init();
void flow_runner_step(const struct FlowInputs* inputs, struct FlowOutputs* outputs);
