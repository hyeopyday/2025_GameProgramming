#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lotto.h"

int main(void)
{
    int i, lotto[6];
    srand(time(NULL));
    generate_lotto_numbers(lotto);

    for (i = 0; i < 6; i++)
        printf("%2d\n", lotto[i]);

    return 0;
}
