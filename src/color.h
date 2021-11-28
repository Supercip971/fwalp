#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

typedef union
{
    struct
    {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    } __attribute__((packed));

    uint32_t raw;
} Color;

#define make_color$(rv, gv, bv, av)                    \
    (Color)                                            \
    {                                                  \
        {                                              \
            .a = (av), .b = (bv), .g = (gv), .r = (rv) \
        }                                              \
    }

#endif
