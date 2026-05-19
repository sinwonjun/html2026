#ifndef MAZE_H
#define MAZE_H
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define ROWS 10
#define COLS 10
#define HEIGHT (2 * ROWS + 1)
#define WIDTH  (2 * COLS + 1)
 
#define WALL  '#'
#define PATH  ' '
#define START 'S'
#define END   'E'
#define ROUTE '.'
 
typedef struct {
    int row;
    int col;
} Position;
 
extern int dr[4];
extern int dc[4];
 
void initMaze(char maze[HEIGHT][WIDTH]);
void printMaze(char maze[HEIGHT][WIDTH]);
void generateMaze(char maze[HEIGHT][WIDTH]);
 
#endif

