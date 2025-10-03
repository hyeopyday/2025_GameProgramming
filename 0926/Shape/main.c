#include <stdio.h>
#include <windows.h>
#include "shape.h"

int main(void) {
     SetConsoleOutputCP(CP_UTF8);   // 출력 UTF-8
    SetConsoleCP(CP_UTF8);         // 입력 UTF-8
    int shape1[3][3] = {
        {0,1,0},
        {0,1,0},
        {1,1,1}
    };

    move_control(shape1);
    return 0;
}
