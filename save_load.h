#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#ifndef BOARDS
#define BOARDS
typedef struct {
	int **plShip;
	int **plShot;
	int **aiShip;
	int **aiShot;
} Boards;
#endif
void saveToFile (int **plShip, int **plShot, int **aiShip, int **aiShot, char *filename, int modeId, int turnMark);
int loadFromFile (Boards *bd, char *filename, int *turnMark, int *gameStyle, int *width, int *heigth);
void saveFreeMode (int width, int heigth, int **plShip, int **plShot, int **aiShip, int **aiShot, char *filename, int modeId, int turnMark);
#endif
