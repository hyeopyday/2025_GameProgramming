#include <stdio.h>
#include "dan.h"

void print_dan(int dan)
{
    int i;
    for (i = 1; i <= 9; i++)
    {
        printf("%d*%d=%d\n", dan, i, dan * i);
    }
}
