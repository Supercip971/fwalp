#ifndef RENDER_H
#define RENDER_H 
#include "config.h"
#include "color.h"
#include "rect.h"
#include <SDL2/SDL.h> 
#include <X11/Xlib.h> 

typedef struct 
{ 
    int width;
    int height;
    uint32_t* color;
    Pixmap * texture; 
    
} FWalpFramebuffer;

typedef struct 
{
    Display* x11_display;

    FWalpFramebuffer framebuffer;
} FWalpRenderer;

FWalpRenderer* render_init(const FWalpConfig* config);

void render_deinit(FWalpRenderer* self);

void render_flip(FWalpRenderer* self);

void render_fill(FWalpRenderer* self, Color col);

void render_rect(FWalpRenderer* self, Rect part, Color col);

void render_pixel(FWalpRenderer* self, int x, int y, Color col);

#endif
