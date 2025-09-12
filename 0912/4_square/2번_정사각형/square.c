#include <stdio.h>
#include "square.h"

void draw_square(int size)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7];
    for (i = 1; i < 7; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);
    for (i = 0; i < size; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");

    for (i = 0; i < size; i++)
    {
        printf("%c%c", a, b[2]);
        for (j = 0; j < size; j++)
            printf(" ");
        printf("%c%c", a, b[2]);
        printf("\n");
    }

    printf("%c%c", a, b[6]);
    for (i = 0; i < size; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}
