#include <stdio.h>
#include <stdlib.h> // system(), rand(), srand()
#include <time.h>   // time() for srand()
#include <conio.h>  // _kbhit(), _getch() for Windows keyboard input
#include <windows.h> // Sleep(), GetAsyncKeyState() for non-blocking input and delay

// --- 게임 설정 ---
#define BOARD_WIDTH 12
#define BOARD_HEIGHT 22 // 위 2줄은 숨겨진 시작 부분

// 블록 모양 (4x4 행렬)
// O 테트리스 모양: 7가지
// I, O, T, S, Z, J, L
const int Tetromino[7][4][4] = {
    // I (0)
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
    // O (1)
    {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // T (2)
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // S (3)
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // Z (4)
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // J (5)
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // L (6)
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}
};

// 보드 상태: 0은 빈 공간, 1~7은 고정된 블록, 8은 현재 떨어지는 블록
int Board[BOARD_HEIGHT][BOARD_WIDTH];
int CurrentTetromino[4][4]; // 현재 떨어지는 블록의 모양
int CurrentType;            // 현재 떨어지는 블록의 종류 (0-6)
int CurrentX, CurrentY;     // 현재 블록의 보드 상 위치 (왼쪽 위 기준)
int Score = 0;
int Level = 1;
int LinesCleared = 0;
int GameOver = 0;

// --- 함수 선언 ---
void InitGame();
void DrawScreen();
void GetNewTetromino();
void CopyTetromino(int dest[4][4], const int src[4][4]);
void RotateTetromino(int tetromino[4][4]);
int CheckCollision(int x, int y, int tetromino[4][4]);
void PlaceTetromino();
void ClearLines();
void GameLoop();
void SetCursorPosition(int x, int y);
void HideCursor();
void SetConsoleColor(int color);

// --- 메인 함수 ---
int main() {
    InitGame();
    GameLoop();

    SetCursorPosition(BOARD_WIDTH * 2, BOARD_HEIGHT + 2);
    SetConsoleColor(7); // 기본 색상으로 복원
    printf("게임 종료! 최종 점수: %d\n", Score);
    
    // 종료 시 콘솔을 바로 닫히지 않도록
    printf("계속하려면 아무 키나 누르십시오...\n");
    getchar(); 

    return 0;
}

// --- 함수 정의 ---

// 커서 위치 설정
void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 커서 숨기기
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    cursor_info.bVisible = FALSE; // 커서 숨김
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 콘솔 색상 설정 (Windows)
void SetConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 게임 초기화
void InitGame() {
    srand((unsigned int)time(NULL));
    HideCursor();
    system("cls"); // 화면 지우기

    // 보드 테두리 설정 및 내부 0으로 초기화
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1) {
                Board[y][x] = 9; // 벽 또는 바닥
            } else {
                Board[y][x] = 0; // 빈 공간
            }
        }
    }

    GetNewTetromino();
}

// 새 블록 생성
void GetNewTetromino() {
    CurrentType = rand() % 7;
    CopyTetromino(CurrentTetromino, Tetromino[CurrentType]);
    CurrentX = (BOARD_WIDTH / 2) - 2; // 중앙에 배치
    CurrentY = 0; // 맨 위에서 시작

    // 시작하자마자 충돌하면 게임 오버 (숨겨진 2줄 포함)
    if (CheckCollision(CurrentX, CurrentY, CurrentTetromino)) {
        GameOver = 1;
    }
}

// 블록 모양 복사
void CopyTetromino(int dest[4][4], const int src[4][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            dest[y][x] = src[y][x];
        }
    }
}

// 블록 회전 (시계 방향 90도)
void RotateTetromino(int tetromino[4][4]) {
    int temp[4][4];
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            temp[x][3 - y] = tetromino[y][x];
        }
    }
    CopyTetromino(tetromino, (const int(*)[4])temp);
}

// 충돌 감지
// x, y: 현재 블록의 왼쪽 위 보드 좌표
int CheckCollision(int x, int y, int tetromino[4][4]) {
    for (int ty = 0; ty < 4; ty++) {
        for (int tx = 0; tx < 4; tx++) {
            if (tetromino[ty][tx] != 0) { // 블록의 한 조각
                int boardX = x + tx;
                int boardY = y + ty;

                // 보드 범위를 벗어나거나, 이미 블록이 있는 곳에 충돌
                if (boardX < 0 || boardX >= BOARD_WIDTH ||
                    boardY < 0 || boardY >= BOARD_HEIGHT ||
                    Board[boardY][boardX] != 0) {
                    return 1; // 충돌 발생
                }
            }
        }
    }
    return 0; // 충돌 없음
}

// 블록을 보드에 고정
void PlaceTetromino() {
    for (int ty = 0; ty < 4; ty++) {
        for (int tx = 0; tx < 4; tx++) {
            if (CurrentTetromino[ty][tx] != 0) {
                Board[CurrentY + ty][CurrentX + tx] = CurrentType + 1; // 1~7로 블록 종류 표시
            }
        }
    }
}

// 완성된 줄 지우기
void ClearLines() {
    int lines_cleared_this_turn = 0;
    for (int y = BOARD_HEIGHT - 2; y >= 0; y--) { // 바닥 위부터 검사
        int full_line = 1;
        for (int x = 1; x < BOARD_WIDTH - 1; x++) { // 테두리 제외
            if (Board[y][x] == 0) {
                full_line = 0;
                break;
            }
        }

        if (full_line) {
            lines_cleared_this_turn++;
            // 해당 줄을 지우고 위에서 한 줄씩 내리기
            for (int dropY = y; dropY > 0; dropY--) {
                for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                    Board[dropY][x] = Board[dropY - 1][x];
                }
            }
            // 맨 위 줄은 비워주기
            for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                Board[0][x] = 0;
            }
            y++; // 현재 줄이 지워지고 위 줄이 내려왔으므로, 다시 현재 줄을 검사해야 함
        }
    }

    if (lines_cleared_this_turn > 0) {
        LinesCleared += lines_cleared_this_turn;
        // 점수 계산 (간단하게)
        Score += lines_cleared_this_turn * 100 * Level;
        // 레벨업 (예: 10줄마다 레벨업)
        if (LinesCleared / 10 + 1 > Level) {
            Level = LinesCleared / 10 + 1;
        }
    }
}

// 화면 그리기
void DrawScreen() {
    SetCursorPosition(0, 0); // 커서를 화면 맨 위로

    // 현재 보드 상태 그리기
    for (int y = 2; y < BOARD_HEIGHT; y++) { // 숨겨진 2줄 제외하고 그리기
        for (int x = 0; x < BOARD_WIDTH; x++) {
            // 현재 떨어지는 블록 그리기
            int is_current_block_part = 0;
            for (int ty = 0; ty < 4; ty++) {
                for (int tx = 0; tx < 4; tx++) {
                    if (CurrentTetromino[ty][tx] != 0 &&
                        CurrentY + ty == y && CurrentX + tx == x) {
                        is_current_block_part = 1;
                        break;
                    }
                }
                if (is_current_block_part) break;
            }

            if (is_current_block_part) {
                SetConsoleColor(CurrentType + 1 + 8); // 블록 종류에 따른 색상 (밝은 색)
                printf("■"); // 현재 블록
            } else if (Board[y][x] == 9) {
                SetConsoleColor(8); // 회색
                printf("□"); // 벽
            } else if (Board[y][x] != 0) {
                SetConsoleColor(Board[y][x] + 8); // 고정된 블록
                printf("■");
            } else {
                SetConsoleColor(7); // 기본 색상
                printf("  "); // 빈 공간
            }
        }
        printf("\n");
    }

    SetConsoleColor(7); // 기본 색상으로 복원
    SetCursorPosition(BOARD_WIDTH * 2 + 2, 0);
    printf("점수: %d", Score);
    SetCursorPosition(BOARD_WIDTH * 2 + 2, 1);
    printf("레벨: %d", Level);
    SetCursorPosition(BOARD_WIDTH * 2 + 2, 2);
    printf("지운 줄: %d", LinesCleared);

    if (GameOver) {
        SetConsoleColor(4); // 빨간색
        SetCursorPosition(BOARD_WIDTH / 2 * 2 - 4, BOARD_HEIGHT / 2);
        printf("GAME OVER!");
    }
}

// 게임 루프
void GameLoop() {
    int fall_timer = 0;
    int fall_delay = 1000; // 블록이 자동으로 떨어지는 시간 (ms)

    while (!GameOver) {
        // --- 입력 처리 ---
        if (_kbhit()) { // 키보드 입력이 있을 경우
            char key = _getch();
            int newX = CurrentX;
            int newY = CurrentY;
            int newTetromino[4][4];
            CopyTetromino(newTetromino, CurrentTetromino);

            switch (key) {
                case 'a': // 왼쪽
                case 'A':
                case 75: // 방향키 왼쪽 (ASCII)
                    newX--;
                    break;
                case 'd': // 오른쪽
                case 'D':
                case 77: // 방향키 오른쪽 (ASCII)
                    newX++;
                    break;
                case 's': // 아래로 빠르게 떨어뜨리기
                case 'S':
                case 80: // 방향키 아래 (ASCII)
                    while (!CheckCollision(CurrentX, CurrentY + 1, CurrentTetromino)) {
                        CurrentY++;
                        Score += 1; // 하드 드롭 시 점수 추가
                    }
                    fall_timer = fall_delay; // 바로 떨어뜨리기 위해 타이머 리셋
                    break;
                case 'w': // 회전
                case 'W':
                case 72: // 방향키 위 (ASCII)
                    RotateTetromino(newTetromino);
                    break;
                case 27: // ESC 키로 종료
                    GameOver = 1;
                    break;
            }

            // 충돌이 없으면 이동/회전 적용
            if (!CheckCollision(newX, newY, newTetromino)) {
                CurrentX = newX;
                CurrentY = newY;
                CopyTetromino(CurrentTetromino, newTetromino);
            }
        }

        // --- 자동 블록 떨어뜨리기 ---
        fall_timer += 50; // 50ms마다 체크
        if (fall_timer >= fall_delay / Level) { // 레벨에 따라 떨어지는 속도 빨라짐
            fall_timer = 0;
            if (!CheckCollision(CurrentX, CurrentY + 1, CurrentTetromino)) {
                CurrentY++; // 아래로 한 칸 이동
            } else {
                // 더 이상 내려갈 수 없으면 보드에 고정
                PlaceTetromino();
                ClearLines();
                GetNewTetromino(); // 새 블록 생성 (여기서 게임 오버 체크)
            }
        }

        // --- 화면 그리기 ---
        DrawScreen();
        
        Sleep(50); // 50ms 대기 (초당 20프레임)
    }
}