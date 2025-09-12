#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "snack.h"

void chicken_burger(void)
{
    system("cls");
    printf("치킨버거 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void cheese_burger(void)
{
    system("cls");
    printf("치즈버거 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void tomato_spaghetti(void)
{
    system("cls");
    printf("토마토 스파게티 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void cream_spaghetti(void)
{
    system("cls");
    printf("크림 스파게티 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void press_any_key(void)
{
    printf("\n\n");
    printf("아무키나 누르면 이전 메뉴로...");
    getch();
}
