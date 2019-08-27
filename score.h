#ifndef SCORE_H
#define SCORE_H
typedef struct {
	char name[50][21];
	int score[50];
} List;
void sort (List *data, int n, int criteria);
void scoreLoad ();
void scoreSave (int score);
#endif