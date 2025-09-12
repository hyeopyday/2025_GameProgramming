#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lotto.h"
#include "sort.h"

int main(void)
{
    int lotto[6];
    srand(time(NULL));
    generate_lotto_numbers(lotto);
    selection_sort(lotto, 6);
    return 0;
}
