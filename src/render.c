#include "render.h"

FWalpRenderer *render_init(const FWalpConfig *config)
{

    FWalpRenderer *renderer = calloc(sizeof(FWalpRenderer), 1);

    if (config->screen_id == 0)
    {
        renderer->x11_display = XOpenDisplay(NULL);
    }
    else
    {
        renderer->x11_display = XOpenDisplay(config->screen_id);
    }

    if (!renderer->x11_display)
    {
        printf("can't open x11 display\n");
        exit(-1);
    }

    const Window x11_window = RootWindow(renderer->x11_display, DefaultScreen(renderer->x11_display));

    SDL_Init(SDL_INIT_VIDEO);

    renderer->sdl_window = SDL_CreateWindowFrom((void *)x11_window);
    renderer->renderer = SDL_CreateRenderer(renderer->sdl_window, -1, SDL_RENDERER_SOFTWARE);

    SDL_GetWindowSize(renderer->sdl_window, &renderer->framebuffer.width, &renderer->framebuffer.height);

    printf("window size: %x, %x\n", renderer->framebuffer.width, renderer->framebuffer.height);
    renderer->framebuffer.texture = SDL_CreateTexture(renderer->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, renderer->framebuffer.width, renderer->framebuffer.height);
    renderer->framebuffer.color = malloc(sizeof(uint32_t) * renderer->framebuffer.width * renderer->framebuffer.height);
    return renderer;
}

void render_deinit(FWalpRenderer *self)
{

    SDL_DestroyTexture(self->framebuffer.texture);
    SDL_DestroyWindow(self->sdl_window);
    SDL_DestroyRenderer(self->renderer);
    free(self->framebuffer.color);
    SDL_Quit();

    XCloseDisplay(self->x11_display);
}

void render_fill(FWalpRenderer *self, Color col)
{
    int count = self->framebuffer.width * self->framebuffer.height;

    for (size_t i = 0; i < count; i++)
    {
        self->framebuffer.color[count] = col;
    }
}

void render_rect(FWalpRenderer *self, Rect part, Color col)
{
    for (size_t y = 0; y < part.h; y++)
    {
        for (size_t x = 0; x < part.w; x++)
        {
            self->framebuffer.color[self->framebuffer.width * (part.y + y) + (part.x + x)] = col;
        }
    }
}

void render_pixel(FWalpRenderer *self, int x, int y, Color col)
{
    if (x + y * self->framebuffer.width > self->framebuffer.width * self->framebuffer.height)
    {
        printf("out of bound render pixel call !\n");
        exit(1);
    }

    self->framebuffer.color[self->framebuffer.width * y + x] = col;
}

void render_flip(FWalpRenderer *self)
{
    SDL_UpdateTexture(self->framebuffer.texture, NULL, self->framebuffer.color, self->framebuffer.width * sizeof(Color));
    SDL_SetRenderDrawColor(self->renderer, 0, 0, 0, 255);
    SDL_RenderClear(self->renderer);
    SDL_RenderCopy(self->renderer, self->framebuffer.texture, NULL, NULL);

    SDL_RenderPresent(self->renderer);
}

bool render_update(FWalpRenderer *self)
{
    SDL_Event ev;
    bool should_quit = false;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            should_quit = true;
            break;
        default:
            break;
        }
    }
    return !should_quit;
}
