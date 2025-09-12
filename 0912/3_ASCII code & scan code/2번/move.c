#include "move.h"

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch (key)
    {
    case 72:
        *y1 = *y1 - 1;
        if (*y1 < 1)
            *y1 = 1;
        break;
    case 75:
        *x1 = *x1 - 1;
        if (*x1 < 1)
            *x1 = 1;
        break;
    case 77:
        *x1 = *x1 + 1;
        if (*x1 > x_b)
            *x1 = x_b;
        break;
    case 80:
        *y1 = *y1 + 1;
        if (*y1 > y_b)
            *y1 = y_b;
        break;
    default:
        return;
    }
}
