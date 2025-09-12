#include <stdio.h>
#include "sum.h"

int main(void)
{
    printf("합계 = %lf\n", sum(2, 10.5, 20.23));
    printf("합계 = %lf\n", sum(5, 10.3, 245.67, 0.51, 198345.764));
    return 0;
}
