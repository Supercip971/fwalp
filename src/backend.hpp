#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <X11/Xlib.h>
#include "color.hpp"
#include "config.hpp"
#include "rect.hpp"
#include "utils.hpp"
namespace fwalp
{
class Backend
{

public:
    virtual ~Backend() = default;
    virtual Result init(fwalp::Config *config) = 0;
    virtual Result deinit() = 0;
    virtual Result update() = 0;
    virtual Result flip() = 0;
    virtual Result fill(fwalp::Color color) = 0;
    virtual Result rect(fwalp::Rect rect, fwalp::Color color) = 0;
    virtual Result pixel(int x, int y, fwalp::Color color) = 0;

    virtual float ticks() = 0;

    virtual uint32_t width() = 0;
    virtual uint32_t height() = 0;

    virtual bool should_close() = 0;
};

} // namespace fwalp
#endif
