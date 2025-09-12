#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "submenu.h"

int sub_menu_display01(void)
{
    int select;
    system("cls");
    printf("햄버거 만들기\n\n");
    printf("1. 치킨버거\n");
    printf("2. 치즈버거\n");
    printf("3. 메인 메뉴로 이동\n\n");
    printf("메뉴번호 입력>");
    select = getch() - 48;
    return select;
}

int sub_menu_display02(void)
{
    int select;
    system("cls");
    printf("스파게티 만들기\n\n");
    printf("1. 토마토 스파게티\n");
    printf("2. 크림 스파게티\n");
    printf("3. 메인 메뉴로 이동\n\n");
    printf("메뉴번호 입력>");
    select = getch() - 48;
    return select;
}
