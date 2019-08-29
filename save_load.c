/*
Author: Paulius Staisiunas. 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include "con_lib.h"
#include "func.h"
void saveToFile (int **plShip, int **plShot, int **aiShip, int **aiShot, char *filename, int modeId, int turnMark){
	FILE *fs = fopen(filename,"wb");
	if (fs){
		con_clear();
		con_set_pos(10,4);
		con_set_color(1,0);
		printf("Please wait while your game is being saved...\n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		int classicModeMark = 0;
		fwrite(&classicModeMark,sizeof(int),1,fs); // 0 = classic 
		fwrite(&modeId, sizeof(int), 1, fs);
		if (modeId == 2){
			fwrite(&turnMark, sizeof(int), 1, fs);
		}

		for (int i = 0; i < 10; i++){
			fwrite(plShip[i],sizeof(int),10,fs);
		}
		for (int i = 0; i < 10; i++){
			fwrite(plShot[i],sizeof(int),10,fs);
		}
		for (int i = 0; i < 10; i++){
			fwrite(aiShip[i],sizeof(int),10,fs);
		}
		for (int i = 0; i < 10; i++){
			fwrite(aiShot[i],sizeof(int),10,fs);
		}
		fclose(fs);
	}
}
int loadFromFile (Boards *bd, char *filename, int *turnMark, int *gameStyle, int *width, int *heigth){
	if (bd->plShip==NULL || bd->plShot==NULL || bd->aiShip==NULL || bd->aiShot==NULL || filename==NULL || turnMark==NULL || gameStyle==NULL || width==NULL || heigth==NULL){
		return -1;
	}
	FILE *fl = fopen(filename,"rb");
	if (fl){
		int modeId = 0;
		fread(gameStyle,sizeof(int),1,fl);
		if (*gameStyle == 0){	// if classic style
			fread(&modeId, sizeof(int), 1, fl);
			if (modeId == 2){
				fread(turnMark, sizeof(int), 1, fl);
			}

			bd->plShip = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				bd->plShip[i] = malloc(sizeof(int)*10);
			}
			bd->plShot = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				bd->plShot[i] = malloc(sizeof(int)*10);
			}
			bd->aiShip = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				bd->aiShip[i] = malloc(sizeof(int)*10);
			}
			bd->aiShot = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				bd->aiShot[i] = malloc(sizeof(int)*10);
			}
			
			for (int i = 0; i < 10; i++){
				fread(bd->plShip[i], sizeof(int), 10, fl);
			}
			for (int i = 0; i < 10; i++){
				fread(bd->plShot[i], sizeof(int), 10, fl);
			}
			for (int i = 0; i < 10; i++){
				fread(bd->aiShip[i], sizeof(int), 10, fl);
			}
			for (int i = 0; i < 10; i++){
				fread(bd->aiShot[i], sizeof(int), 10, fl);
			}

			fclose(fl);
			return modeId;
		}
		if (*gameStyle == 1){	// if free style
			fread(&modeId, sizeof(int), 1, fl);
			if (modeId == 2){
				fread(turnMark, sizeof(int), 1, fl);
			}

			fread(heigth,sizeof(int),1,fl);
			fread(width,sizeof(int),1,fl);

			bd->plShip = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				bd->plShip[i] = malloc(sizeof(int)*(*width));
			}
			bd->plShot = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				bd->plShot[i] = malloc(sizeof(int)*(*width));
			}
			bd->aiShip = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				bd->aiShip[i] = malloc(sizeof(int)*(*width));
			}
			bd->aiShot = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				bd->aiShot[i] = malloc(sizeof(int)*(*width));
			}

			for (int i = 0; i < *width; i++){
				fread(bd->plShip[i], sizeof(int), *width, fl);
			}
			for (int i = 0; i < *width; i++){
				fread(bd->plShot[i], sizeof(int), *width, fl);
			}
			for (int i = 0; i < *width; i++){
				fread(bd->aiShip[i], sizeof(int), *width, fl);
			}
			for (int i = 0; i < *width; i++){
				fread(bd->aiShot[i], sizeof(int), *width, fl);
			}
			fclose(fl);
			return modeId;
		}
	}
	else {
		return -1;
	}
}
void saveFreeMode (int width, int heigth, int **plShip, int **plShot, int **aiShip, int **aiShot, char *filename, int modeId, int turnMark){
	FILE *fs = fopen(filename,"wb");
	if (fs){
		con_clear();
		con_set_pos(10,4);
		con_set_color(1,0);
		printf("Please wait while your game is being saved...\n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(1,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		con_set_color(0,0);
		con_sleep(0.1);
		con_set_pos(10,6);
		printf(" \n");
		int freeModeMark = 1;
		fwrite(&freeModeMark,sizeof(int),1,fs); // 1 = free game style
		fwrite(&modeId, sizeof(int), 1, fs);
		if (modeId == 2){
			fwrite(&turnMark, sizeof(int), 1, fs);
		}

		fwrite(&heigth,sizeof(int),1,fs);
		fwrite(&width,sizeof(int),1,fs);

		for (int i = 0; i < width; i++){
			fwrite(plShip[i],sizeof(int),width,fs);
		}
		for (int i = 0; i < width; i++){
			fwrite(plShot[i],sizeof(int),width,fs);
		}
		for (int i = 0; i < width; i++){
			fwrite(aiShip[i],sizeof(int),width,fs);
		}
		for (int i = 0; i < width; i++){
			fwrite(aiShot[i],sizeof(int),width,fs);
		}				

		fclose(fs);
	}
}
