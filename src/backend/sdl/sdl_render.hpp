#pragma once

#include <SDL2/SDL.h>
#include <X11/Xlib.h>
#include <memory>
#include "backend.hpp"
#include "color.hpp"
#include "config.hpp"
#include "rect.hpp"
namespace fwalp
{
class SDLBackend : public Backend
{
    int _width;
    int _height;
    bool _should_exit;
    std::unique_ptr<Color> _raw_buffer;
    SDL_Texture *_texture;
    Display *_x11_display;
    SDL_Window *_sdl_window;
    SDL_Renderer *_renderer;

public:
    ~SDLBackend(){};
    virtual uint32_t width() { return _width; };
    virtual uint32_t height() { return _height; };
    virtual Result init(fwalp::Config *config);
    virtual Result deinit();
    virtual Result update();
    virtual Result flip();
    virtual Result fill(fwalp::Color color);
    virtual Result rect(fwalp::Rect rect, fwalp::Color color);
    virtual Result pixel(int x, int y, fwalp::Color color);

    virtual float ticks();
    virtual bool should_close() { return _should_exit; };
};
} // namespace fwalp
