#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <X11/Xlib.h>
#include <stdbool.h>
#include "color.h"
#include "config.h"
#include "rect.h"

typedef struct
{
    int width;
    int height;
    uint32_t *color;
    SDL_Texture *texture;

} FWalpFramebuffer;

typedef struct
{
    Display *x11_display;
    SDL_Window *sdl_window;
    SDL_Renderer *renderer;
    FWalpFramebuffer framebuffer;
} FWalpRenderer;

FWalpRenderer *render_init(const FWalpConfig *config);

void render_deinit(FWalpRenderer *self);

void render_flip(FWalpRenderer *self);

void render_fill(FWalpRenderer *self, Color col);

void render_rect(FWalpRenderer *self, Rect part, Color col);

void render_pixel(FWalpRenderer *self, int x, int y, Color col);

bool render_update(FWalpRenderer *self);
#endif
