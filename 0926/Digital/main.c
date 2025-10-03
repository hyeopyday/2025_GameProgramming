#include <stdio.h>
#include "digit.h"

int main(void) {
    int num, line;
    printf("디지털 숫자 출력 프로그램\n");
    printf("1 이상의 정수를 입력하세요: ");
    scanf("%d", &num);

    for (line = 0; line < 5; line++) {   // 5줄 (0~4)
        number_check(num, laine);
        printf("\n");
    }

    return 0;
}
