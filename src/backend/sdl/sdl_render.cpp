#include "backend/sdl/sdl_render.hpp"

namespace fwalp
{
Result SDLBackend::init(fwalp::Config *config)
{

    _should_exit = 0;
    if (config->screen_id == "0" || config->screen_id.length() == 0)
    {
        _x11_display = XOpenDisplay(NULL);
    }
    else
    {
        _x11_display = XOpenDisplay(config->screen_id.c_str());
    }

    if (!_x11_display)
    {
        printf("can't open x11 display\n");
        exit(-1);
    }

    const Window x11_window = RootWindow(_x11_display, DefaultScreen(_x11_display));

    SDL_Init(SDL_INIT_VIDEO);

    _sdl_window = SDL_CreateWindowFrom((void *)x11_window);
    _renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_SOFTWARE);

    SDL_GetWindowSize(_sdl_window, &_width, &_height);

    printf("window size: %x, %x\n", _width, _height);
    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, _width, _height);
    _raw_buffer = std::make_unique<Color>(_width * _height);

    return Result::success();
}
Result SDLBackend::deinit()
{
    SDL_DestroyTexture(_texture);
    SDL_DestroyWindow(_sdl_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    XCloseDisplay(_x11_display);
    return Result::success();
}
Result SDLBackend::update()
{
    SDL_Event ev;
    _should_exit = false;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            _should_exit = true;
            break;
        default:
            break;
        }
    }
    return Result::success();
}
Result SDLBackend::flip()
{
    SDL_UpdateTexture(_texture, NULL, _raw_buffer.get(), _width * sizeof(Color));
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, NULL, NULL);

    SDL_RenderPresent(_renderer);
    return Result::success();
}
Result SDLBackend::fill(fwalp::Color color)
{
    int count = _width * _height;

    for (int i = 0; i < count; i++)
    {
        _raw_buffer.get()[i] = color;
    }
    return Result::success();
}
Result SDLBackend::rect(fwalp::Rect rect, fwalp::Color color)
{
    for (int y = 0; y < rect.h; y++)
    {
        for (int x = 0; x < rect.w; x++)
        {
            _raw_buffer.get()[_width * (rect.y + y) + (rect.x + x)] = color;
        }
    }
    return Result::success();
}
Result SDLBackend::pixel(int x, int y, fwalp::Color color)
{
#ifdef DEBUG
    if (x + y * _width > _width * _height)
    {
        return Result::failure("pixel out of bounds");
    }
#endif

    _raw_buffer.get()[_width * (y) + (x)] = color;

    return Result::success();
}

float SDLBackend::ticks()
{
    return SDL_GetTicks();
}
} // namespace fwalp
