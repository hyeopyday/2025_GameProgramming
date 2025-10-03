#include <stdio.h>
#include <string.h>
int main(void)
{
    char number[20];
    int length, i;
    printf("금액을 입력하고 Enter>");
    scanf("%s", number);
    length = strlen(number);
    for (i = 0; i < length; i++)
        printf("%c\n", number[i]);
    return 0;
}

void serial_number(long number)
{
    int num;
    int i, length = 0;
    length = (int)(log10(number) + 1); // 최대 자리수 계산
    for (i = length; i >= 1; i--)
    {
        num = number / (long)pow(10, i - 1);
        printf("%ld\n", num);
        number = number - num * (long)pow(10, i - 1);
    }
    printf("\n");
}