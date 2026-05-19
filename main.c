#include "maze.h"
#include "stack.h"
#include <windows.h>

// 색상 설정 함수
void setColor(int text, int bg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + bg * 16);
}

// 색상으로 미로 출력
void printColorMaze(char maze[HEIGHT][WIDTH], int curR, int curC) {
    int i, j;
	for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            // 현재 셀 = 노란 배경
            if (i == 2 * curR + 1 && j == 2 * curC + 1) {
                setColor(0, 14);   // 검정 글씨 + 노란 배경
                printf("**");
            }
            else if (maze[i][j] == WALL) {
                setColor(8, 8);    // 회색 벽
                printf("  ");
            }
            else if (maze[i][j] == PATH) {
                setColor(15, 0);   // 흰 통로
                printf("  ");
            }
            else if (maze[i][j] == START) {
                setColor(10, 0);   // 초록 S
                printf("S ");
            }
            else if (maze[i][j] == END) {
                setColor(12, 0);   // 빨강 E
                printf("E ");
            }
            else {
                setColor(7, 0);
                printf("%c ", maze[i][j]);
            }
        }
        setColor(7, 0);
        printf("\n");
    }
    setColor(7, 0);
}

// 스택 내용 출력
void printStack(Stack *s) {
    printf("  Stack: [");
    int i;
	for (i = 0; i <= s->top; i++) {
        printf("(%d,%d)", s->data[i].row, s->data[i].col);
        if (i < s->top) printf(", ");
    }
    printf("]\n");
}

// 사용자 입력 대기
void waitEnter(void) {
    printf("\n  >>> Enter 키를 눌러 다음 단계로...\n");
    getchar();
}

int main(void) {
    // 3x3 미로로 설정 (maze.h에서 ROWS=3, COLS=3 일 때)
    char maze[HEIGHT][WIDTH];
    int visited[ROWS][COLS] = {0};
    Stack stack;
    int step = 1;

    srand((unsigned int)time(NULL));
    stackInit(&stack);
    initMaze(maze);

    char *dirName[] = {"위", "아래", "왼쪽", "오른쪽"};

    printf("========================================\n");
    printf("   DFS 미로 생성 시뮬레이션 (%dx%d)\n", ROWS, COLS);
    printf("========================================\n\n");

    // Step 1: 시작 셀
    visited[0][0] = 1;
    Position start = {0, 0};
    stackPush(&stack, start);

    printf("[Step %d] 시작 셀 (0,0)을 Push하고 방문 표시\n", step++);
    printStack(&stack);
    printf("\n");
    printColorMaze(maze, 0, 0);
    waitEnter();

    // DFS 루프
    while (!stackIsEmpty(&stack)) {
        Position current = stackPeek(&stack);
        int r = current.row;
        int c = current.col;

        // 미방문 이웃 찾기
        Position neighbors[4];
        int dirs[4];
        int count = 0;
		int i, j;
        for (i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS
                && !visited[nr][nc]) {
                neighbors[count].row = nr;
                neighbors[count].col = nc;
                dirs[count] = i;
                count++;
            }
        }

        system("cls");  // 화면 지우기

        if (count > 0) {
            // 랜덤으로 이웃 선택
            int idx = rand() % count;
            Position next = neighbors[idx];
            int dir = dirs[idx];

            // 벽 제거
            int wallR = r + next.row + 1;
            int wallC = c + next.col + 1;
            maze[wallR][wallC] = PATH;

            // 방문 처리 및 Push
            visited[next.row][next.col] = 1;
            stackPush(&stack, next);

            printf("[Step %d] (%d,%d) -> (%d,%d) %s 이동\n",
                step++, r, c, next.row, next.col, dirName[dir]);
            printf("  벽 제거: maze[%d][%d]\n", wallR, wallC);
            printf("  공식: wallR = %d+%d+1 = %d, wallC = %d+%d+1 = %d\n",
                r, next.row, wallR, c, next.col, wallC);
            printStack(&stack);
            printf("\n");
            printColorMaze(maze, next.row, next.col);
        }
        else {
            // 백트래킹
            Position popped = stackPop(&stack);

            if (!stackIsEmpty(&stack)) {
                Position prev = stackPeek(&stack);
                printf("[Step %d] (%d,%d) 미방문 이웃 없음 -> Pop! (백트래킹)\n",
                    step++, popped.row, popped.col);
                printf("  (%d,%d)로 돌아감\n", prev.row, prev.col);
                printStack(&stack);
                printf("\n");
                printColorMaze(maze, prev.row, prev.col);
            }
            else {
                printf("[Step %d] (%d,%d) Pop! -> 스택 비어짐\n",
                    step++, popped.row, popped.col);
                printStack(&stack);
                printf("\n");
                printColorMaze(maze, -1, -1);
            }
        }

        waitEnter();
    }

    // 완성
    system("cls");
    maze[1][1] = START;
    maze[HEIGHT - 2][WIDTH - 2] = END;

    printf("========================================\n");
    printf("   미로 생성 완료! (총 %d단계)\n", step - 1);
    printf("========================================\n\n");
    printColorMaze(maze, -1, -1);

    printf("\n  모든 셀이 연결된 완전한 미로가 만들어졌습니다!\n");

    return 0;
}
