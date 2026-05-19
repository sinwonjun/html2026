#include "maze.h"
 
int main(void) {
    char maze[HEIGHT][WIDTH];
    srand((unsigned int)time(NULL));
    initMaze(maze);
    maze[1][1] = START;
    maze[HEIGHT-2][WIDTH-2] = END;
    printf("=== 미로 초기 상태 ===\n");
    printMaze(maze);
    return 0;
}

