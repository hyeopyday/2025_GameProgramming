#include <stdio.h>
#include "square.h"

int main(void)
{
    int n;
    printf("정사각형 그리기\n\n");
    printf("정사각형의 길이(최대 37)를\n");
    printf("입력하고 Enter>");
    scanf("%d", &n);
    draw_square(n);
    return 0;
}
