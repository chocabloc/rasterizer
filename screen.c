#include "screen.h"
#include "window.h"
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define SIGN(x) ((0 < (x)) - ((x) < 0))

// convert to screen coordinates
static void to_screen_coords(vec2_t* v)
{
    v->x = (v->x + 1) * (SCREEN_WIDTH / 2);
    v->y = (1 - v->y) * (SCREEN_HEIGHT / 2);
}

// draw point at (x, y)
void scr_point(vec2_t p)
{
    to_screen_coords(&p);
    win_put(round(p.x), round(p.y));
}

// draw line from (x1, y1) to (x2, y2)
void scr_line(vec2_t a, vec2_t b)
{
    to_screen_coords(&a);
    to_screen_coords(&b);

    int dx = b.x - a.x, dy = b.y - a.y;
    float adx = fabs(dx), ady = fabs(dy);
    float xf = SIGN(dx), yf = SIGN(dy);
    if (adx > ady)
        yf = dy / adx;
    else
        xf = dx / ady;

    float x = a.x, y = a.y;
    for (int i = 0; i <= MAX(adx, ady); i++) {
        win_put((int)x, (int)y);
        x += xf;
        y += yf;
    }
}