#include <stdio.h>
#include "digit.h"

// 숫자 배열 정의
int zero[20]  = {1,1,1,1, 1,0,0,1, 1,0,0,1, 1,0,0,1, 1,1,1,1};
int one[20]   = {0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0};
int two[20]   = {1,1,1,1, 0,0,0,1, 1,1,1,1, 1,0,0,0, 1,1,1,1};
int three[20] = {1,1,1,1, 0,0,0,1, 1,1,1,1, 0,0,0,1, 1,1,1,1};
int four[20]  = {1,0,0,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1};
int five[20]  = {1,1,1,1, 1,0,0,0, 1,1,1,1, 0,0,0,1, 1,1,1,1};
int six[20]   = {1,1,1,1, 1,0,0,0, 1,1,1,1, 1,0,0,1, 1,1,1,1};
int seven[20] = {1,1,1,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1};
int eight[20] = {1,1,1,1, 1,0,0,1, 1,1,1,1, 1,0,0,1, 1,1,1,1};
int nine[20]  = {1,1,1,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 1,1,1,1};


// 숫자 한 줄 출력
void digit_print(int dim[], int line) {
    int i;
    for (i = line*4; i < line*4+4; i++) {
        if (dim[i] == 1)
            printf("■"); // 블록 문자
        else
            printf(" ");
    }
    printf(" ");
}

// 숫자 전체 체크
void number_check(int k, int i) {
    if (k >= 1) {
        number_check(k/10, i);
        switch(k % 10) {
            case 0: digit_print(zero, i); break;
            case 1: digit_print(one, i); break;
            case 2: digit_print(two, i); break;
            case 3: digit_print(three, i); break;
            case 4: digit_print(four, i); break;
            case 5: digit_print(five, i); break;
            case 6: digit_print(six, i); break;
            case 7: digit_print(seven, i); break;
            case 8: digit_print(eight, i); break;
            case 9: digit_print(nine, i); break;
        }
    }
}
