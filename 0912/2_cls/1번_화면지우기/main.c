#include <stdio.h>
#include "screen.h"

int main(void)
{
    char ch;
    printf("문자를 입력하고 Enter>");
    scanf("%c", &ch);
    clear_screen();
    printf("입력된 문자 %c\n", ch);
    return 0;
}
