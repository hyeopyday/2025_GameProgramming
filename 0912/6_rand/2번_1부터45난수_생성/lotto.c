#include <stdlib.h>
#include "lotto.h"

int generate_lotto_number(void)
{
    return rand() % 45 + 1;
}
