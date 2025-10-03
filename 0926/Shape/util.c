#include <stdio.h>
#include <windows.h>
#include "shape.h"

// 커서 이동
void gotoxy(int x, int y) {
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 조작 안내 출력
void print_direction(void) {
    gotoxy(25, 1);
    printf("화살표: 이동, 스페이스: 회전");
}
