#ifndef RECT_H
#define RECT_H

namespace fwalp
{
struct Rect
{
    int x;
    int y;
    int w;
    int h;

    Rect(){};
    Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h){};
};
} // namespace fwalp
#endif
