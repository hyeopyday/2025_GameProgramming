#include <stdarg.h>
#include "sum.h"

double sum(int count, ...)
{
    double total = 0, number;
    int i = 0;
    va_list ap;
    va_start(ap, count);
    while (i < count)
    {
        number = va_arg(ap, double);
        total += number;
        i++;
    }
    va_end(ap);
    return total;
}
