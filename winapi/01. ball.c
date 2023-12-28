#define API__1
#include "api.h"

BEGIN()

static int x = 0;
static int y = 0;
static int dx = 1;
static int dy = 1;
int delay = 10;

EXAM89_BEGIN(delay)

    CIRCLE(x, y, 30, 30);

    x += (dx * 10);
    y += (dy * 10);

    if (x <= 0 || x+30 >= WIDTH) {
        dx *= -1;
    }

    if (y <= 0 || y+30 >= HEIGHT) {
        dy *= -1;
    }

EXAM89_END()   
 
END()