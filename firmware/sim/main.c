/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "SDL2/SDL.h"
#include "gfx.h"
#include "flow_runner.h"
#include "midi_backend.h"
#include "wntr_deque.h"
#include "stel_math_utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Macros, constants, and types */

static const float colors[][3] = {
    {0.3f, 0.3f, 0.3f},
    {0.5f, 0.5f, 0.5f},
    {0.85f, 0.25f, 0.36f},  // red 4
    {0.25f, 0.55f, 0.58f},  // teal 4
    {0.49f, 0.38f, 0.73f},  // purple 4
    {0.75f, 0.14f, 0.21f},  // red 5
    {0.15f, 0.47f, 0.50f},  // teal 5
    {0.37f, 0.25f, 0.62f},  // teal 6
    {0.85f, 0.25f, 0.36f},  // red 4
    {0.25f, 0.55f, 0.58f},  // teal 4
    {0.49f, 0.38f, 0.73f},  // purple 4
};

struct InOut {
    struct FlowInputs inputs;
    struct FlowOutputs outputs;
};

/* Static variables */
static struct FlowInputs inputs;
static struct FlowOutputs outputs;
#define HISTORY_LEN 60 * 5
static struct InOut history[HISTORY_LEN];
static struct WntrDeque history_deque = {
    .data = (uint8_t*)(history),
    .item_size = sizeof(struct InOut),
    .capacity = HISTORY_LEN,
};
static long frame_count = 0;
static long loop_count = 0;

/* Forward declarations */
static bool handle_events();
static void draw(cairo_t* cr);
static void plot_history(cairo_t* cr, size_t offset, float min, float max, uint8_t row);

/* Main */
int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    midi_backend_init();

    WntrDeque_init(&history_deque);

    gfx_init();

    flow_runner_init();

    bool done = false;
    while (!done) {
        done = handle_events();

        for (int i = 0; i < 5; i++) {
            inputs.a = -5.0f + fmod(SDL_GetTicks() / 1000.f, 1.f) * 10.0f;
            flow_runner_step(&inputs, &outputs);
            loop_count++;
        }

        struct InOut snapshot = {
            .inputs = inputs,
            .outputs = outputs,
        };

        WntrDeque_push(&history_deque, (uint8_t*)(&snapshot));

        cairo_t* cr = gfx_start(0.25f, 0.55f, 0.58f);
        draw(cr);
        gfx_end();
        frame_count++;
    }

    gfx_deinit();
}

/* Private functions */

static void draw(cairo_t* cr) {
    cairo_select_font_face(cr, "Roboto", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

    /* Graphs */
    plot_history(cr, offsetof(struct InOut, inputs.a), -5.0f, 5.0f, 0);
    plot_history(cr, offsetof(struct InOut, inputs.b), -5.0f, 5.0f, 1);
    plot_history(cr, offsetof(struct InOut, outputs.one), -5.0f, 8.0f, 2);
    plot_history(cr, offsetof(struct InOut, outputs.two), -5.0f, 8.0f, 3);
    plot_history(cr, offsetof(struct InOut, outputs.three), -5.0f, 8.0f, 4);
    plot_history(cr, offsetof(struct InOut, outputs.four), -5.0f, 8.0f, 5);
    plot_history(cr, offsetof(struct InOut, outputs.delta), -5.0f, 5.0f, 6);
    plot_history(cr, offsetof(struct InOut, outputs.gamma), -5.0f, 5.0f, 7);

    /* Frame count and iteration count*/
    char buf[256];

    cairo_set_font_size(cr, 16);
    cairo_set_source_rgba(cr, 1, 1, 1, 1.0);

    sprintf(buf, "N: %lu F: %lu", loop_count, frame_count);
    cairo_move_to(cr, 8, 24);
    cairo_show_text(cr, buf);
}

static bool handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return true;
                break;
            default:
                break;
        }
    }
    return false;
}

static void plot_history(cairo_t* cr, size_t offset, float min, float max, uint8_t row) {
    float size = ((float)(CANVAS_HEIGHT)) / 8.0f / 2.0f;
    float padding = 2.0f;
    float center_y = size + (2.f * size * row);
    float extent = size - (2.f * padding);

    /* Draw box */
    cairo_set_source_rgba(cr, colors[row][0], colors[row][1], colors[row][2], 1);
    cairo_rectangle(cr, 0, center_y - size, CANVAS_WIDTH, size * 2);
    cairo_fill(cr);

    /* Draw the 0 point line */
    cairo_set_line_width(cr, 1.0);
    cairo_set_source_rgba(cr, 1, 1, 1, 0.7f);
    cairo_set_dash(cr, (double[]){2.f}, 1, 0);
    float midpoint_y = center_y + extent * (-1.f * map_rangef(0.f, min, max, -1.f, +1.f));
    cairo_move_to(cr, 0, midpoint_y);
    cairo_line_to(cr, CANVAS_WIDTH, midpoint_y);
    cairo_stroke(cr);

    /* Draw the data */
    cairo_set_dash(cr, NULL, 0, 0);
    cairo_set_source_rgba(cr, 1, 1, 1, 1);
    cairo_set_line_width(cr, 3.0);

    struct WntrDequeIter iter = {.q = &history_deque};
    struct InOut elem;
    float elem_v;
    WntrDequeIter_init(&iter);
    while (WntrDequeIter_next(&iter, (uint8_t*)&elem)) {
        elem_v = *((float*)((uint8_t*)(&elem) + offset));

        float v = -1.f * map_rangef(elem_v, min, max, -1.f, +1.f);

        float x = (float)(iter.n) * ((float)(CANVAS_WIDTH) / (float)(HISTORY_LEN));
        float y = center_y + (extent * v);

        if (iter.n == 1) {
            cairo_move_to(cr, 0, y);
        } else {
            cairo_line_to(cr, x, y);
        }
    }
    cairo_stroke(cr);

    /* Draw the latest value */
    cairo_set_font_size(cr, 12);
    char buf[32];
    sprintf(buf, "%.02f", elem_v);
    cairo_move_to(cr, CANVAS_WIDTH - 28, center_y + size - 8);
    cairo_show_text(cr, buf);
}
