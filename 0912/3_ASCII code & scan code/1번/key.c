#include <stdio.h>
#include <conio.h>
#include "key.h"

void print_key_code(int ch)
{
    if (ch == 0 || ch == 0xe0)
    {
        ch = getch();
        printf("확장키 code=%d\n", ch);
    }
    else
    {
        printf("아스키 code=%d\n", ch);
    }
}
