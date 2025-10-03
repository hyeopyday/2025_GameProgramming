#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "slide.h"

int main(void) {
    char *slide = "■", key;
    int x = 1, y = 1;
    int h_slide_length, v_slide_length;

    printf("슬라이드바 표시\n");
    printf("가로 슬라이드바의 길이(최대 70)를 입력: ");
    scanf("%d", &h_slide_length);

    printf("세로 슬라이드바의 길이(최대 19)를 입력: ");
    scanf("%d", &v_slide_length);

    system("cls");

    do {
        draw_vertical_slide(1, y, v_slide_length, slide);
        draw_horizontal_slide(x, v_slide_length + 3, h_slide_length, slide);
        key = getch();
        move_arrow_key(key, &x, &y, h_slide_length, v_slide_length);
    } while (key != 27); // ESC 입력 시 종료

    return 0;
}
