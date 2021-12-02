#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

namespace fwalp
{

union Color
{
    struct
    {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    } __attribute__((packed));

    uint32_t raw;

    Color() : raw(0){};
    Color(uint32_t raw) : raw(raw){};
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : b(b), g(g), r(r), a(a){};
};

} // namespace fwalp
#endif
