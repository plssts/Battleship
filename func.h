/*
Author: Paulius Staisiunas. 2016
*/

#ifndef GAME_F
#define GAME_F
typedef struct{
	int x, y;
}Point;

typedef struct{
	Point *pt;
	int size;
}Stack;

typedef struct {
	char name[50][21];
	int score[50];
} List;

#ifndef BOARDS
#define BOARDS
typedef struct {
	int **plShip;
	int **plShot;
	int **aiShip;
	int **aiShot;
} Boards;
#endif

void seeTime ();
void changePl ();
void sort (List *data, int n, int criteria);
void scoreLoad ();
void scoreSave (int score);
void sizeSelect(int *width, int *heigth, int *engineCount);
void rmsingl (int **board);
void rembrd (Boards *bd, int width);
void nulbrd (Boards *bd);
void grid_t(int x, int y);
void grid ();
void push (Stack *stack, Point pt);
void printBoards (int **playerShip, int **playerShot, int width, int heigth);
void printShips (int **board, int width, int heigth);
void initStack (Stack *stack);
int setScr (int cursx, int cursy, int **plShip, int gameStyle, int width, int heigth, int engineCount);

int saveScr (int **plShip, int **plShot, int **aiShip, int **aiShot, int modeId, int turnMark, int gameStyle, int width, int heigth);
/** 
*	modeId = gamemode (2 players or 1 player).
*	1 player modeId = 1, turnMark = 0 (not used).
*	2 player modeId = 2, turnMark = 0 (player2) or turnMark = 1 (player1).
*	turnMark determines who has priority.
**/

int homeScr ();
int game (int **aiShip, int **aiShot, int **plShip, int **plShot, int gameStyle, int width, int heigth);
int aiSet (int **board, int gameStyle, int width, int heigth, int engineCount);
void initBoard (int board[10][10]);
void helpScr ();
int gameMP (int **plShip, int **plShot, int **aiShip, int **aiShot, int turnMark, int gameStyle, int width, int heigth);
int newScr();
#endif
