#include <stdio.h>
#include <windows.h>
#include "slide.h"

// 사각형 출력
void draw_rectangle(int c, int r) {
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7];
    for (i = 1; i < 7; i++) b[i] = 0xa0 + i;

    printf("%c%c%c", a, b[3], a);
    for (i = 0; i < c; i++) printf("%c%c", a, b[1]);
    printf("%c%c%c\n", a, b[4], a);

    for (i = 0; i < r; i++) {
        printf("%c%c%c", a, b[6], a);
        for (j = 0; j < c; j++) printf("  ");
        printf("%c%c%c\n", a, b[5], a);
    }
}

// 커서 이동
void gotoxy(int x, int y) {
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
