#include <stdlib.h>
#include "lotto.h"

void generate_lotto_numbers(int r[6])
{
    int i, j;
    for (i = 0; i < 6; i++)
    {
        r[i] = rand() % 45 + 1;
        for (j = 0; j < i; j++)
        {
            if (r[i] == r[j])
            {
                i--;
                break;
            }
        }
    }
}
