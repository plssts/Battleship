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
*	modeId = zaidimo rezimas (2 zaidejai/1 zaidejas).
*	1 zaidejo rezimu modeId = 1, o turnMark = 0 (siuo atveju 0 net nenuskaitomas).
*	2 zaideju rezimu modeId = 2, o turnMark = 0 (player2) arba turnMark = 1 (player1).
*	Cia turnMark nusako 1-ojo arba 2-ojo zaidejo prioriteta sauti lentoje.
**/

int homeScr ();
int game (int **aiShip, int **aiShot, int **plShip, int **plShot, int gameStyle, int width, int heigth);
int aiSet (int **board, int gameStyle, int width, int heigth, int engineCount);
void initBoard (int board[10][10]);
void helpScr ();
int gameMP (int **plShip, int **plShot, int **aiShip, int **aiShot, int turnMark, int gameStyle, int width, int heigth);
int newScr();
#endif
