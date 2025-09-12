#include <stdlib.h>
#include "lotto.h"

void generate_lotto_numbers(int lotto[6])
{
    int i, j;
    for (i = 0; i < 6; i++)
    {
        lotto[i] = rand() % 45 + 1;
        for (j = 0; j < i; j++)
        {
            if (lotto[i] == lotto[j])
            {
                i--;
                break;
            }
        }
    }
}
