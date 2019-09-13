/*
Author: Paulius Staisiunas. 2016
*/

#include "con_lib.h"
#include "func.h"
#include "save_load.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

int main(int argc, char** argv) {
	struct tm *timingStart;
	time_t rawtime;
	time(&rawtime);
	timingStart = localtime(&rawtime);

	FILE *flog = fopen("log.txt","a");
	fprintf(flog,"Program run time: %s",asctime(timingStart));
	fclose(flog);

	time_t start;
	time(&start);
	FILE *fo = fopen("log.txt","ab");
	fseek(fo,0,SEEK_END);
	fwrite(&start,sizeof(time_t),1,fo);
	fclose(fo);

 	con_show_echo(0);
 	con_show_cursor(0);

	int x_place = 5, y_place = 5;
	int pre_game_status = 0;

	srand(time(NULL));

	Boards BRD;
	int turnMark;

	while (1){
		fflush(stdout);
		con_clear();
		int home_status = homeScr();
		con_clear();
		if (home_status == 1){
			int mode_status = newScr();
			if (mode_status == 4){ 								// MP FREE
				int width = 0, heigth = 0, engineCount = 0;
				sizeSelect(&width,&heigth,&engineCount);

				BRD.plShip = malloc(sizeof(int*)*heigth);
				for (int i = 0; i < heigth; i++){
					BRD.plShip[i] = malloc(sizeof(int)*width);
				}
				for (int i = 0; i < width; i++){
					for (int j = 0; j < heigth; j++){
						BRD.plShip[j][i] = 0;
					}
				}
				BRD.aiShip = malloc(sizeof(int*)*heigth);
				for (int i = 0; i < heigth; i++){
					BRD.aiShip[i] = malloc(sizeof(int)*width);
				}
				for (int i = 0; i < width; i++){
					for (int j = 0; j < heigth; j++){
						BRD.aiShip[j][i] = 0;
					}
				}
				int p1_status = setScr(1,1,BRD.plShip,1,width,heigth,engineCount);
				int p2_status;
				if (p1_status){
					p2_status = setScr(1,1,BRD.aiShip,1,width,heigth,engineCount);
				}
				if (p1_status == 1 && p2_status == 1){
					BRD.plShot = malloc(sizeof(int*)*heigth);
					for (int i = 0; i < heigth; i++){
						BRD.plShot[i] = malloc(sizeof(int)*width);
					}
					BRD.aiShot = malloc(sizeof(int*)*heigth);
					for (int i = 0; i < heigth; i++){
						BRD.aiShot[i] = malloc(sizeof(int)*width);
					}
					con_clear();
					gameMP(BRD.plShip,BRD.plShot,BRD.aiShip,BRD.aiShot,1,1,width,heigth);
					rembrd(&BRD,heigth);
				}
			}
			if (mode_status == 3){ 								// SP FREE
				int width = 0, heigth = 0, engineCount = 0;
				sizeSelect(&width,&heigth,&engineCount);
				BRD.plShip = malloc(sizeof(int*)*heigth);
				for (int i = 0; i < heigth; i++){
					BRD.plShip[i] = malloc(sizeof(int)*width);
				}
				for (int i = 0; i < width; i++){
					for (int j = 0; j < heigth; j++){
						BRD.plShip[j][i] = 0;
					}
				}
				BRD.aiShip = malloc(sizeof(int*)*heigth);
				for (int i = 0; i < heigth; i++){
					BRD.aiShip[i] = malloc(sizeof(int)*width);
				}
				for (int i = 0; i < width; i++){
					for (int j = 0; j < heigth; j++){
						BRD.aiShip[j][i] = 0;
					}
				}
				pre_game_status = setScr(1,1,BRD.plShip,1,width,heigth,engineCount);
				int ai_status = aiSet(BRD.aiShip,1,width,heigth,engineCount);
				if (ai_status == 1 && pre_game_status == 1){
					BRD.plShot = malloc(sizeof(int*)*heigth);
					for (int i = 0; i < heigth; i++){
						BRD.plShot[i] = malloc(sizeof(int)*width);
					}
					BRD.aiShot = malloc(sizeof(int*)*heigth);
					for (int i = 0; i < heigth; i++){
						BRD.aiShot[i] = malloc(sizeof(int)*width);
					}
					game(BRD.aiShip, BRD.aiShot, BRD.plShip, BRD.plShot, 1, width, heigth);
					rembrd(&BRD,heigth);
				}
			}
			if (mode_status == 2){ 								// MP CLASSIC
				nulbrd(&BRD);
				int p1_status = setScr(x_place,y_place,BRD.plShip,0,10,10,0);
				int p2_status;
				if (p1_status){
					p2_status = setScr(x_place,y_place,BRD.aiShip,0,10,10,0);
				}
				if (p1_status == 1 && p2_status == 1){
					con_clear();
					printf("Player 1 starts the game.\nPress any key to continue.");
					getchar();
					con_clear();
					gameMP(BRD.plShip,BRD.plShot,BRD.aiShip,BRD.aiShot,1,0,10,10);
					rembrd(&BRD,10);
				}
			}
			if (mode_status == 1){ 								//SP CLASSIC
				nulbrd(&BRD);
				pre_game_status = setScr(x_place, y_place, BRD.plShip,0,10,10,0);
				int ai_status = aiSet(BRD.aiShip,0,10,10,0);

				if (pre_game_status == 1 && ai_status == 1){
					int game_outcome = game(BRD.aiShip, BRD.aiShot, BRD.plShip, BRD.plShot, 0, 10, 10);//2 = saved, 1 = won, 0 = lost
					rembrd(&BRD,10);
				}
			}
		}
		if (home_status == 2){
			int turnMark, gameStyle, width, heigth;
			int load_status = loadFromFile(&BRD,"save_1.txt",&turnMark,&gameStyle,&width,&heigth);
			if (load_status == -1){
				continue; //no save files. Currently one save file is looked for
			}

			if (load_status == 1 && gameStyle == 0){
				int game_outcome = game(BRD.aiShip, BRD.aiShot, BRD.plShip, BRD.plShot, 0, 10, 10);
				nulbrd(&BRD);
			}
			if (load_status == 2 && gameStyle == 0){
				int game_outcome = gameMP(BRD.plShip, BRD.plShot, BRD.aiShip, BRD.aiShot, turnMark, 0, width, heigth);
				nulbrd(&BRD);
			}
			if (load_status == 1 && gameStyle == 1){
				int game_outcome = game(BRD.aiShip, BRD.aiShot, BRD.plShip, BRD.plShot, 1, width, heigth);
			}
			if (load_status == 2 && gameStyle == 1){
				int game_outcome = gameMP(BRD.plShip, BRD.plShot, BRD.aiShip, BRD.aiShot, turnMark, 1, width, heigth);
			}
		}
		if (home_status == 3){
			helpScr();
		}
		if (home_status == 4){
			scoreLoad();
		}
		if (home_status == 5){
			atexit(seeTime);
			return 0;
		}
	}
	return 0;
}

