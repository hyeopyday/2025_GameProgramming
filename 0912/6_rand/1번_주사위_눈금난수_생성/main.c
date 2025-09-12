#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dice.h"

int main(void)
{
    int i;
    srand(time(NULL));
    for (i = 1; i <= 10; i++)
        printf("%2d:%d\n", i, roll_dice());
    return 0;
}
