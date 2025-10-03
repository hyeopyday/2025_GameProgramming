#include <stdio.h>
#include "slide.h"

// 가로 슬라이드 출력
void draw_horizontal_slide(int x, int y, int length, char *s) {
    int real_length = length / 2;
    gotoxy(1, y);
    draw_rectangle(real_length + 1, 1);
    gotoxy(x + 2, y);
    printf("%s", s);
    gotoxy(real_length * 2 + 2, y - 1);
    printf("%2d", x);
}

// 세로 슬라이드 출력
void draw_vertical_slide(int x, int y, int length, char *s) {
    gotoxy(x, 1);
    draw_rectangle(1, length);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(x + 6, length + 1);
    printf("%2d", y);
}

// 방향키 이동 처리
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch (key) {
        case 72: // ↑ 위
            (*y1)--;
            if (*y1 < 1) *y1 = 1;
            break;
        case 75: // ← 왼쪽
            (*x1)--;
            if (*x1 < 1) *x1 = 1;
            break;
        case 77: // → 오른쪽
            (*x1)++;
            if (*x1 > x_b) *x1 = x_b;
            break;
        case 80: // ↓ 아래
            (*y1)++;
            if (*y1 > y_b) *y1 = y_b;
            break;
        default:
            return;
    }
}
