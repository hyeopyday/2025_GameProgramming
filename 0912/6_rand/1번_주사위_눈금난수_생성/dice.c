#include <stdlib.h>
#include "dice.h"

int roll_dice(void)
{
    return rand() % 6 + 1;
}
