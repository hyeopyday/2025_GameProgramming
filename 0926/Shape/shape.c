#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "shape.h"

// 전역 좌표
int x = 35, y = 12;
int inx = 0, iny = 0;

// 도형 회전 (시계 방향)
void rotation_right(int m[3][3]) {
    int i, j;
    int temp[3][3];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            temp[j][2 - i] = m[i][j];

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            m[i][j] = temp[i][j];
}

// 도형 출력
void print_shape(int m[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        gotoxy(x, y + i);
        for (j = 0; j < 3; j++) {
            if (m[i][j] == 1)
                printf("■");
            else
                printf("  ");
        }
        printf("\n");
    }
}

// 도형 이동
void move_shape(int m[3][3]) {
    do {
        system("cls");
        print_shape(m);
        print_direction();

        x += inx;
        y += iny;

        if (y > 23) y = 23;
        else if (y < 2) y = 2;

        if (x > 75) x = 75;
        else if (x < 1) x = 1;

        Sleep(100);
    } while (!kbhit());
}

// 입력 제어 (방향키/스페이스바)
void move_control(int m[3][3]) {
    char key;
    do {
        while (!kbhit()) {
            system("cls");
            move_shape(m);
        }
        key = getch();
        switch (key) {
            case 32: // 스페이스: 회전
                rotation_right(m);
                move_shape(m);
                break;
            case 72: // ↑
                inx = 0; iny = -1;
                move_shape(m);
                break;
            case 75: // ←
                inx = -1; iny = 0;
                move_shape(m);
                break;
            case 77: // →
                inx = 1; iny = 0;
                move_shape(m);
                break;
            case 80: // ↓
                inx = 0; iny = 1;
                move_shape(m);
                break;
            default:
                break;
        }
    } while (key != 27); // ESC 종료
    printf("\n");
}
