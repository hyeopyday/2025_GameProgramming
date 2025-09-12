#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lotto.h"

int main(void)
{
    int i;
    srand(time(NULL));
    for (i = 1; i <= 6; i++)
        printf("%2d:%d\n", i, generate_lotto_number());
    return 0;
}
