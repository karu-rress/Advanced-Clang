#define API__2
#include "api.h"
#include <math.h>

BEGIN()

int px, py;
int x, y;
double angle;
double radian;

EXAM90_BEGIN()

    LINE(50,  50,  50, HEIGHT - 50);
    LINE(50, (HEIGHT-100)/2 + 50, WIDTH - 50, (HEIGHT - 100)/2 + 50);
    
    px = 50;
    py = (HEIGHT - 100) / 2 + 50;

    for (angle = 0; angle <= 630; angle++) {
        radian = angle * 3.141592 / 180;

        x = px + (int)angle;
        y = py + -(int)(sin(radian) * 100);

        PIXEL(x, y);
    }

EXAM90_END()
 
END()