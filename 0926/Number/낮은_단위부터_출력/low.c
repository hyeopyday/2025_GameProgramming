#include <stdio.h>
#include <string.h>
int main(void)
{
    char number[20];
    int length, i;
    printf("금액을 입력하고 Enter>");
    scanf("%s", number);
    length = strlen(number);
    for (i = length; i >= 0; i--)
        printf("%c\n", number[i]);
    return 0;
}
void reverse_number(long number)
{
    while (number > 0)
    {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}