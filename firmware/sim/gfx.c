/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "gfx.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Surface* sdl_surface;
static SDL_Texture* texture;
static cairo_surface_t* cr_surface;
static cairo_t* cr;
static int window_width;
static int window_height;
static int renderer_width;
static int renderer_height;

void gfx_init() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Stellar",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CANVAS_WIDTH,
        CANVAS_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_GetWindowSize(window, &window_width, &window_height);

    printf(
        "window_width=%d\n"
        "window_height=%d\n",
        window_width,
        window_height);

    SDL_GetRendererOutputSize(renderer, &renderer_width, &renderer_height);

    printf(
        "renderer_width=%d\n"
        "renderer_height=%d\n",
        renderer_width,
        renderer_height);

    texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, renderer_width, renderer_height);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

cairo_t* gfx_start(float r, float g, float b) {
    void* pixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &pixels, &pitch);

    int cairo_x_multiplier = renderer_width / window_width;
    int cairo_y_multiplier = renderer_height / window_height;

    cr_surface =
        cairo_image_surface_create_for_data(pixels, CAIRO_FORMAT_ARGB32, renderer_width, renderer_height, pitch);

    cairo_surface_set_device_scale(cr_surface, cairo_x_multiplier, cairo_y_multiplier);

    cr = cairo_create(cr_surface);

    cairo_set_source_rgba(cr, r, g, b, 1.0);
    cairo_rectangle(cr, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    cairo_fill(cr);

    return cr;
}

void gfx_end() {
    cairo_destroy(cr);
    cairo_surface_destroy(cr_surface);

    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void gfx_deinit() {
    SDL_FreeSurface(sdl_surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
