#include <stdio.h>
#include "sort.h"

void selection_sort(int r[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (r[j] < r[min])
                min = j;
        }
        temp = r[min];
        r[min] = r[i];
        r[i] = temp;
    }

    for (i = 0; i < n; i++)
        printf("%2d\n", r[i]);
}
