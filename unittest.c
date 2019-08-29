#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "con_lib.h"
#include "func.h"
#include "save_load.h"
int my_setScr (int cursx, int cursy, int **plShip, int gameStyle, int width, int heigth, int engineCount){
	int rotation_mark = 0, eng_num = 5;
	int threeship = 2;
	if (cursx>width || cursy>heigth || cursx<0 || cursy<0 || plShip==NULL || gameStyle<0 || gameStyle>1 || width<0 || heigth<0 || width>20 || heigth>10 || engineCount<1 || engineCount>(width*heigth)/3){
		return 0;
	}
	if (gameStyle == 0){
  		while(1){

			grid_t(10,10);
			int key = 0;

			int x_place = (cursx - 1)*3 + 2;
			int y_place = (cursy - 1)*2 + 2;
		
			con_set_color(2,0);
			printShips(plShip,10,10);

			con_set_color(1,0);
			if (rotation_mark == 0){
				for (int i = 0; i < (3*eng_num); i=i+3){
					con_set_pos(x_place+i, y_place);
					printf("~~");
				}
			}
			if (rotation_mark == 1){
				for (int i = 0; i < (2*eng_num); i=i+2){
					con_set_pos(x_place, y_place+i);
					printf("~~");
				}
			}
			con_set_color(0,7);
			fflush(stdout);

    		while (key = con_read_key()){
      			if (key == 'w'){
					if (rotation_mark == 0){
						for (int i = 0; i < (3*eng_num); i=i+3){
							con_set_pos(x_place+i, y_place);
							printf("  ");
        				}
					}
					if (rotation_mark == 1){
						for (int i = 0; i < (2*eng_num); i=i+2){
							con_set_pos(x_place, y_place+i);
							printf("  ");
						}
					}
					if (cursy > 1){
						cursy--;
					}

      			}
				else if (key == 's'){
       				if (rotation_mark == 0){
						for (int i = 0; i < (3*eng_num); i=i+3){
							con_set_pos(x_place+i, y_place);
							printf("  ");
						}
        			}
					if (rotation_mark == 1){
						for (int i = 0; i < (2*eng_num); i=i+2){
							con_set_pos(x_place, y_place+i);
							printf("  ");
						}
					}
					if (rotation_mark == 0 && (cursy + 1) <= 10){
						cursy++;
					}
					if (rotation_mark == 1 && (cursy + eng_num) <= 10){
						cursy++;
					}
      			}
				else if (key == 'a'){
        			if (rotation_mark == 0 && cursx >= 1){
						for (int i = 0; i < (3*eng_num); i=i+3){
							con_set_pos(x_place+i, y_place);
							printf("  ");
						}
        			}
					if (rotation_mark == 1 && (cursy - 1)>=0){
						for (int i = 0; i < (2*eng_num); i=i+2){
							con_set_pos(x_place, y_place+i);
							printf("  ");
						}
					}
					if (cursx > 1){
						cursx--;
					}
      			}
				else if (key == 'd'){
        			if (rotation_mark == 0 && (cursx + eng_num) <= 10){
						for (int i = 0; i < (3*eng_num); i=i+3){
							con_set_pos(x_place+i, y_place);
							printf("  ");
						}
        			}
					if (rotation_mark == 1 && (cursy + 1) <= 10){
						for (int i = 0; i < (2*eng_num); i=i+2){
							con_set_pos(x_place, y_place+i);
							printf("  ");
						}
					}
					if (rotation_mark == 0 && cursx + eng_num <=10){
						cursx++;
					}
					if (rotation_mark == 1 && (cursx + 1)<=10){
						cursx++;
					}
      			}
				else if (key == 'r'){
					if (rotation_mark == 0){
						rotation_mark = 1;
						for (int i = 0; i < (3*eng_num); i=i+3){
							con_set_pos(x_place+i, y_place);
							printf("  ");
						}
						cursx = 4;
						cursy = 4;
						continue;
					}
					if (rotation_mark == 1){
						rotation_mark = 0;
						for (int i = 0; i < (2*eng_num); i=i+2){
							con_set_pos(x_place, y_place+i);
							printf("  ");
						}
						cursx = 4;
						cursy = 4;
						continue;
					}
				}
				else if (key == 'p'){
					int legit = 1;		
					if (rotation_mark == 0 && legit == 1){
						for (int i = 0; i < 10; i++){		// FIXME: What is THIS FOR for?
							for (int j = 0; j < eng_num; j++){
								if (plShip[cursy-1][cursx-1+j] == 1){	// there is a previous ship here (horizontally)
									legit = 0;
								}
							}
						}
					}
					if (rotation_mark == 1 && legit == 1){
						for (int i = 0; i < 10; i++){
							for (int j = 0; j < eng_num; j++){
								if (plShip[cursy-1+j][cursx-1] == 1){	// there is a previous ship here (vertically)
									legit = 0;
								}
							}
						}
					}

					double distance = 0;
					Stack valid;
					initStack(&valid);
					for (int i = 0; i < 10; i++){
						for (int j = 0; j < 10; j++){
							if (plShip[j][i] == 1){
								int ygr = j+1;
								int xgr = i+1;
								Point point;
								point.x = xgr; 
								point.y = ygr;
								push(&valid,point); //saving current player boats
							}
						}
					}

					if (rotation_mark == 0 && legit == 1){
						for (int i = 0; i < valid.size; i++){
							for (int j = 0; j < eng_num; j++){
								int x1 = cursx + j, x2 = valid.pt[i].x;
								int y1 = cursy, y2 = valid.pt[i].y;
								distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
								if (distance < 1.5){
									legit = 0;
								}
							}
						}
					}
					if (rotation_mark == 1 && legit == 1){
						for (int i = 0; i < valid.size; i++){
							for (int j = 0; j < eng_num; j++){
								int x1 = cursx, x2 = valid.pt[i].x;
								int y1 = cursy + j, y2 = valid.pt[i].y;
								distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
								if (distance < 1.5){
									legit = 0;
								}
							}
						}
					}
					initStack(&valid);

					if (eng_num - 1 >= 1 && legit == 1){
						for (int i = 0; i < (10*3)+2 ;i++){
							for (int j = 0; j < (10*2)+2; j++){
								con_set_pos(i,j);
								printf("  ");
							}
						}
						if (rotation_mark == 0 && legit == 1){
							for (int i = 0; i < eng_num; i++){
								plShip[cursy-1][cursx-1+i] = 1;
							}
							if (eng_num == 3 && threeship == 1){
								eng_num--;
								threeship--;
								continue;
							}
							if (eng_num == 3 && threeship == 2){
								threeship--;
							}
							if (eng_num != 3){
								eng_num--;
							}
						}
						if (rotation_mark == 1 && legit == 1){
							for (int i = 0; i < eng_num; i++){
								plShip[cursy-1+i][cursx-1] = 1;
							}
							if (eng_num == 3 && threeship == 1){
								eng_num--;
								threeship--;
								continue;
							}
							if (eng_num == 3 && threeship == 2){
								threeship--;
							}
							if (eng_num != 3){
								eng_num--;
							}
						}
					}
					if (eng_num - 1 < 1){
						return 1;
					}
				}
				else if (key == 'q'){
       				return 0;
      			}			
			}
		}
	}
	if (gameStyle == 1){
		while(1){

			grid_t(width,heigth);
			int key = 0;

			int x_place = (cursx - 1)*3 + 2;
			int y_place = (cursy - 1)*2 + 2;
		
			con_set_color(2,0);
			printShips(plShip,width,heigth);

			con_set_color(1,0);
			con_set_pos(x_place, y_place);
			printf("~~");
			con_set_color(0,7);
			fflush(stdout);

    		while (key = con_read_key()){
      			if (key == 'w'){
					con_set_pos(x_place, y_place);
					printf("  ");
					if (cursy > 1){
						cursy--;
					}

      			}
				else if (key == 's'){
					con_set_pos(x_place, y_place);
					printf("  ");
					if ((cursy + 1) <= heigth){
						cursy++;
					}
      			}
				else if (key == 'a'){					
					con_set_pos(x_place, y_place);
					printf("  ");	
					if (cursx > 1){
						cursx--;
					}
      			}
				else if (key == 'd'){
					con_set_pos(x_place, y_place);
					printf("  ");
					if ((cursx + 1)<= width){
						cursx++;
					}
      			}
				else if (key == 'p'){
					int legit = 1;
					if (plShip[cursy-1][cursx-1] == 1){
						legit = 0;
					}
					if (legit == 1){
						for (int i = 0; i < (width*3)+2 ;i++){
							for (int j = 0; j < (heigth*2)+2; j++){
								con_set_pos(i,j);
								printf("  ");
							}
						}
						plShip[cursy-1][cursx-1] = 1;
						engineCount--;
					}
					if (engineCount - 1 < 0){
						return 1;
					}
				}
				else if (key == 'q'){
       				return 0;
      			}			
			}
		}
	}
}
int my_saveScr (int **plShip, int **plShot, int **aiShip, int **aiShot, int modeId, int turnMark, int gameStyle, int width, int heigth){
	if (plShip==NULL || plShot==NULL || aiShip==NULL || aiShot==NULL || modeId<1 || modeId>2 || turnMark<0 || turnMark>1 || gameStyle<0 || gameStyle>1 || width<0 || heigth<0 || width>20 || heigth>10){
		return 0;
	}
	con_set_color(3,0);
	con_set_pos(40,10);
	printf("| |\n");
	con_sleep(0.2);
	con_set_pos(39,10);
	printf("|   |\n");
	con_sleep(0.15);
	con_set_pos(38,10);
	printf("|     |\n");
	con_sleep(0.12);
	con_set_pos(37,10);
	printf("|      |\n");
	con_sleep(0.09);
	con_set_pos(36,10);
	printf("|       |\n");
	con_sleep(0.06);
	con_set_pos(43,10);
	printf("|        |\n");
	con_sleep(0.03);
	con_set_pos(42,10);
	printf("|         |\n");
	con_sleep(0.01);
	con_set_pos(41,10);
	printf("|          |\n");
	con_sleep(0.009);
	con_set_pos(40,10);
	printf("|           |\n");
	con_sleep(0.007);
	con_set_pos(39,10);
	printf("|            |\n");
	con_sleep(0.005);
	con_set_pos(38,10);
	printf("|             |\n");
	con_sleep(0.002);
	con_set_pos(37,10);
	printf("|              |\n");
	con_sleep(0.002);
	con_set_pos(36,10);
	printf("|               |\n");
	con_sleep(0.002);
	con_set_pos(35,10);
	printf("|                |\n");
	con_sleep(0.002);
	con_set_pos(34,10);
	printf("|                 |\n");
	con_sleep(0.002);
	con_set_pos(33,10);
	printf("|                  |\n");
	con_sleep(0.002);
	con_set_pos(32,10);
	printf("|                   |\n");
	con_sleep(0.002);
	con_set_pos(31,10);
	printf("|                    |\n");
	con_sleep(0.002);
	con_set_pos(30,10);
	printf("|                     |\n");
	con_sleep(0.002);
	con_set_pos(29,10);
	printf("|                      |\n");
	con_sleep(0.002);
	con_set_pos(28,10);
	printf("|                       |\n");
	con_sleep(0.002);
	con_set_pos(27,10);
	printf("|                        |\n");
	con_sleep(0.002);
	con_set_pos(26,10);
	printf("|                         |\n");
	con_sleep(0.002);
	con_set_pos(25,10);
	printf("|                          |\n");
	con_sleep(0.002);
	con_set_pos(24,10);
	printf("|                           |\n");
	con_sleep(0.002);
	con_set_pos(23,10);
	printf("|                            |\n");
	con_sleep(0.002);
	con_set_pos(23,10);
	printf("|                             |\n");
	con_sleep(0.002);
	con_set_pos(22,10);
	printf("|                              |\n");
	con_sleep(0.002);
	con_set_pos(22,10);
	printf("|                               |\n");
	con_sleep(0.002);
	con_set_pos(21,10);
	printf("|                                |\n");
	con_sleep(0.002);
	con_set_pos(21,10);
	printf("|                                 |\n");
	con_sleep(0.002);
	con_set_pos(20,10);
	printf("|                                  |\n");
	con_sleep(0.002);
	con_set_pos(20,10);
	printf("|                                       |\n");
	fflush(stdout);
	while(1){
		con_sleep(0.09);
		con_set_pos(24,10);
		printf("Would you like to save your game?\n");
		int key = 0;
		while (key = con_read_key()){
			if (key == 'y'){
				con_set_color(0,3);
				printf("| |\n");
				con_sleep(0.002);
				con_set_pos(39,10);
				printf("|  |\n");
				con_sleep(0.002);
				con_set_pos(38,10);
				printf("|   |\n");
				con_sleep(0.002);
				con_set_pos(37,10);
				printf("|    |\n");
				con_sleep(0.002);
				con_set_pos(36,10);
				printf("|     |\n");
				con_sleep(0.002);
				con_set_pos(43,10);
				printf("|     |\n");
				con_sleep(0.002);
				con_set_pos(42,10);
				printf("|      |\n");
				con_sleep(0.002);
				con_set_pos(41,10);
				printf("|       |\n");
				con_sleep(0.002);
				con_set_pos(40,10);
				printf("|         |\n");
				con_sleep(0.002);
				con_set_pos(39,10);
				printf("|         |\n");
				con_sleep(0.002);
				con_set_pos(38,10);
				printf("|           |\n");
				con_sleep(0.002);
				con_set_pos(37,10);
				printf("|           |\n");
				con_sleep(0.002);
				con_set_pos(36,10);
				printf("|             |\n");
				con_sleep(0.002);
				con_set_pos(35,10);
				printf("|              |\n");
				con_sleep(0.002);
				con_set_pos(34,10);
				printf("|               |\n");
				con_sleep(0.002);
				con_set_pos(33,10);
				printf("|               |\n");
				con_sleep(0.002);
				con_set_pos(32,10);
				printf("|                 |\n");
				con_sleep(0.002);
				con_set_pos(31,10);
				printf("|                 |\n");
				con_sleep(0.002);
				con_set_pos(30,10);
				printf("|                   |\n");
				con_sleep(0.002);
				con_set_pos(29,10);
				printf("|                    |\n");
				con_sleep(0.002);
				con_set_pos(28,10);
				printf("|                     |\n");
				con_sleep(0.002);
				con_set_pos(27,10);
				printf("|                       |\n");
				con_sleep(0.002);
				con_set_pos(26,10);
				printf("|                         |\n");
				con_sleep(0.005);
				con_set_pos(25,10);
				printf("|                          |\n");
				con_sleep(0.007);
				con_set_pos(24,10);
				printf("|                           |\n");
				con_sleep(0.009);
				con_set_pos(23,10);
				printf("|                            |\n");
				con_sleep(0.01);
				con_set_pos(23,10);
				printf("|                              |\n");
				con_sleep(0.03);
				con_set_pos(22,10);
				printf("|                                |\n");
				con_sleep(0.06);
				con_set_pos(22,10);
				printf("|                                  |\n");
				con_sleep(0.09);
				con_set_pos(21,10);
				printf("|                                   |\n");
				con_sleep(0.12);
				con_set_pos(21,10);
				printf("|                                    |\n");
				con_sleep(0.15);
				con_set_pos(20,10);
				printf("|                                      |\n");
				con_sleep(0.2);
				con_set_pos(20,10);
				printf("|                                       |\n");
				con_clear();
				if (gameStyle == 0){
					saveToFile(plShip, plShot, aiShip, aiShot, "save_1.txt", modeId, turnMark);
				}
				if (gameStyle == 1){
					saveFreeMode(width,heigth,plShip,plShot,aiShip,aiShot,"save_1.txt",modeId,turnMark);
				}
				fflush(stdout);
				return 1;
			}
			else if (key == 'n'){
				con_set_color(0,3);
				printf("| |\n");
				con_sleep(0.002);
				con_set_pos(39,10);
				printf("|  |\n");
				con_sleep(0.002);
				con_set_pos(38,10);
				printf("|   |\n");
				con_sleep(0.002);
				con_set_pos(37,10);
				printf("|    |\n");
				con_sleep(0.002);
				con_set_pos(36,10);
				printf("|     |\n");
				con_sleep(0.002);
				con_set_pos(43,10);
				printf("|     |\n");
				con_sleep(0.002);
				con_set_pos(42,10);
				printf("|      |\n");
				con_sleep(0.002);
				con_set_pos(41,10);
				printf("|       |\n");
				con_sleep(0.002);
				con_set_pos(40,10);
				printf("|         |\n");
				con_sleep(0.002);
				con_set_pos(39,10);
				printf("|         |\n");
				con_sleep(0.002);
				con_set_pos(38,10);
				printf("|           |\n");
				con_sleep(0.002);
				con_set_pos(37,10);
				printf("|           |\n");
				con_sleep(0.002);
				con_set_pos(36,10);
				printf("|             |\n");
				con_sleep(0.002);
				con_set_pos(35,10);
				printf("|              |\n");
				con_sleep(0.002);
				con_set_pos(34,10);
				printf("|               |\n");
				con_sleep(0.002);
				con_set_pos(33,10);
				printf("|               |\n");
				con_sleep(0.002);
				con_set_pos(32,10);
				printf("|                 |\n");
				con_sleep(0.002);
				con_set_pos(31,10);
				printf("|                 |\n");
				con_sleep(0.002);
				con_set_pos(30,10);
				printf("|                   |\n");
				con_sleep(0.002);
				con_set_pos(29,10);
				printf("|                    |\n");
				con_sleep(0.002);
				con_set_pos(28,10);
				printf("|                     |\n");
				con_sleep(0.002);
				con_set_pos(27,10);
				printf("|                       |\n");
				con_sleep(0.002);
				con_set_pos(26,10);
				printf("|                         |\n");
				con_sleep(0.005);
				con_set_pos(25,10);
				printf("|                          |\n");
				con_sleep(0.007);
				con_set_pos(24,10);
				printf("|                           |\n");
				con_sleep(0.009);
				con_set_pos(23,10);
				printf("|                            |\n");
				con_sleep(0.01);
				con_set_pos(23,10);
				printf("|                              |\n");
				con_sleep(0.03);
				con_set_pos(22,10);
				printf("|                                |\n");
				con_sleep(0.06);
				con_set_pos(22,10);
				printf("|                                  |\n");
				con_sleep(0.09);
				con_set_pos(21,10);
				printf("|                                   |\n");
				con_sleep(0.12);
				con_set_pos(21,10);
				printf("|                                    |\n");
				con_sleep(0.15);
				con_set_pos(20,10);
				printf("|                                      |\n");
				con_sleep(0.2);
				con_set_pos(20,10);
				printf("|                                       |\n");
				con_clear();
				fflush(stdout);
				return 0;
			}
		}
	}
}
int my_game (int **aiShip, int **aiShot, int **plShip, int **plShot, int gameStyle, int width, int heigth){
	int cursx = 1, cursy = 1, player_priv = 1, ai_priv = 0, last_x = 0, last_y = 0, savedQuit = 0, goHome = 0, playerScore = 0;
	Stack shooting;
	initStack(&shooting); // for storing ai successful shots
	if (aiShip==NULL || aiShot==NULL || plShip==NULL || plShot==NULL || gameStyle<0 || gameStyle>1 || width<0 || heigth<0 || width>20 || heigth>10){
		return -1;
	}
	while(1){
		grid_t(width,heigth);

		if (player_priv){
			con_set_color(2,0);
			con_set_pos(41,2);
			printf(" ");
			con_set_color(0,2);
			con_set_pos(42,2);
			printf("  Your turn\n");
		}
		if (player_priv == 0){
			con_set_color(1,0);
			con_set_pos(41,2);
			printf(" ");
			con_set_color(0,1);
			con_set_pos(42,2);
			printf("  Your turn\n");
		}
		if (ai_priv){
			con_set_color(0,2);
			con_set_pos(42,3);
			printf("  PC's turn\n");
		}
		if (ai_priv == 0){
			con_set_color(0,1);
			con_set_pos(42,3);
			printf("  PC's turn\n");
		}
		con_set_color(0,7);
		
		if (gameStyle == 0){
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					if (aiShot[j][i] == -1){
						int ygr = j;
						int xgr = i;
						Point point;
						point.x = xgr; point.y = ygr;
						push(&shooting, point); //saving current ai successful hits
					}
				}
			}
		}		

		int x_place = (cursx - 1)*3 + 2;
		int y_place = (cursy - 1)*2 + 2;
		int key = 0;

		printBoards(plShip, plShot,width,heigth);
		int endCheck = 1;
		if (player_priv){
			for (int i = 0; i < heigth; i++){
				for (int j = 0; j < width; j++){
					if (aiShip[i][j] == 1){
						endCheck = 0;
					}
				}
			}
			if (endCheck){
				scoreSave(playerScore);
				return 1;   /// PLAYER WON THE GAME //
			}
			con_set_pos(x_place, y_place);
			con_set_color(0,1);
			printf("**");
			con_set_color(0,7);
		
			while (key = con_read_key()){
      			if (key == 'w'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
				if (cursy > 1){
					cursy--;
				}
      			} else if (key == 's'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if ((cursy + 1)<=heigth){
						cursy++;
					}
      			} else if (key == 'a'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if (cursx > 1){
						cursx--;
					}
      			} else if (key == 'd'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if ((cursx + 1)<=width){
						cursx++;
					}
      			} else if (key == 'p'){
					if (plShot[cursy-1][cursx-1] == 0){
						plShot[cursy-1][cursx-1] = 1;
					}
					if (aiShip[cursy-1][cursx-1] == 1){
						plShot[cursy-1][cursx-1] = -1;
						aiShip[cursy-1][cursx-1] = 0;
						player_priv = 1;
						playerScore++;
						ai_priv = 0;
					}
					else{
						player_priv = 0;
						ai_priv = 1;
					}
				}
				else if (key == 'q'){
					int save_status = saveScr(plShip, plShot, aiShip, aiShot, 1, 0, gameStyle, width, heigth);
					if (save_status == 1){
						savedQuit = 1;
					}
					if (save_status == 0){
						goHome = 1;
					}
      			}
			}
		}
		if (savedQuit == 1 || goHome == 1){
			return 2; // PLAYER SAVED THE GAME OR ATTEMPTED TO - quit anyway//
		}
		int ai_x = 0, ai_y = 0;
		if (ai_priv){
			con_set_color(1,0);
			con_set_pos(41,2);
			printf(" ");
			con_set_color(0,1);
			con_set_pos(42,2);
			printf("  Your turn\n");
			con_set_color(0,7);
			con_set_color(0,2);
			con_set_pos(42,3);
			printf("  PC's turn\n");
			con_set_color(0,7);
			con_sleep(1);
			int at_zero = 0; // at the first time with stack = 0
			if (gameStyle == 0){
				if (shooting.size == 0){ // if no previous hits
					ai_x = 1+rand()%10;
					ai_y = 1+rand()%10;
					aiShot[ai_y-1][ai_x-1] = 1;// do a hit against player check
					if (plShip[ai_y-1][ai_x-1] == 1){
						ai_priv = 1;
						player_priv = 0;
						plShip[ai_y-1][ai_x-1] = -1;
						aiShot[ai_y-1][ai_x-1] = -1; //mark as hit for ai to check later (and to include -1s in stack)
						at_zero = 1;
					}
					else {
						ai_priv = 0;
						player_priv = 1;
						at_zero = 1;
					}
				}
			}
			endCheck = 1;
			for (int i = 0; i < heigth; i++){
				for (int j = 0; j < width; j++){
					if (plShip[i][j] == 1){
						endCheck = 0; // if player got defeated, exit game with breaker value as 1
					}
				}
			}
			if (endCheck){
				return 0;			// PLAYER LOST THE GAME //
			}  
			if (gameStyle == 0){
				int legal = 0, cycle_count = 0, broken = 0;
				while(legal == 0 && shooting.size > 0 && at_zero == 0){
					ai_x = rand()%10; 
					ai_y = rand()%10;
					int measure;
					cycle_count++;
					for (int i = 0; i < shooting.size; i++){
						measure = abs(shooting.pt[i].x - ai_x) + abs(shooting.pt[i].y - ai_y);
						if (measure == 1 && aiShot[ai_y][ai_x] == 0){ // if close and not tried there, do a shot
							aiShot[ai_y][ai_x] = 1;
							legal = 1;
							if (plShip[ai_y][ai_x] == 1){
								ai_priv = 1;
								player_priv = 0;
								plShip[ai_y][ai_x] = -1;
								aiShot[ai_y][ai_x] = -1; //mark as hit for ai to check later (and to include -1s in stack)
							}
							else {
								ai_priv = 0;
								player_priv = 1;
							}
						}
					}
					if (cycle_count >= 5000){
						broken = 1;
						break;
					}
				}
				if (broken){// if search was not successful, generate random
					ai_x = 1+rand()%10;
					ai_y = 1+rand()%10;
					aiShot[ai_y-1][ai_x-1] = 1;// do a hit against player check
					if (plShip[ai_y-1][ai_x-1] == 1){
						ai_priv = 1;
						player_priv = 0;
						plShip[ai_y-1][ai_x-1] = -1;
						aiShot[ai_y-1][ai_x-1] = -1; //mark as hit for ai to check later (and to include -1s in stack)
					}
					else {
						ai_priv = 0;
						player_priv = 1;
					}

				}
			}
			if (gameStyle == 1){
				while(1){
					ai_x = 1+rand()%(width);
					ai_y = 1+rand()%(heigth);
					if (aiShot[ai_y-1][ai_x-1] == 0){
						aiShot[ai_y-1][ai_x-1] = 1;
						if (plShip[ai_y-1][ai_x-1] == 1){
							ai_priv = 1;
							player_priv = 0;
							plShip[ai_y-1][ai_x-1] = -1;
						}
						else {
							ai_priv = 0;
							player_priv = 1;
						}
						break;
					}
				}
			}
		}
		fflush(stdout);	
	}
}
int my_aiSet (int **board, int gameStyle, int width, int heigth, int engineCount){
	int rotation_mark, eng_num = 5;
	int threeship = 2;

	Stack valid;
	initStack(&valid);
	if (board==NULL || width<0 || heigth<0 || width>20 || heigth>10 || engineCount<1 || engineCount>(width*heigth)/3){
		return 0;
	}

  	while(1){
		if (gameStyle == 0){
			int legit = 1;
			rotation_mark = rand()%2;
			int x_rand = 1+rand()%10;
			int y_rand = 1+rand()%10;

			if (rotation_mark == 1){ //vertical check
				if (y_rand + eng_num < 10){
					legit = 1;
				}
				else {
					legit = 0;
				}
			}
			if (rotation_mark == 0){ //horizontal check
				if (x_rand + eng_num < 10){
					legit = 1;
				}
				else {
					legit = 0;
				}
			}
			if (rotation_mark == 0 && legit == 1){
				for (int i = 0; i < 10; i++){
					for (int j = 0; j < eng_num; j++){
						if (board[y_rand-1][x_rand+j-1] == 1){	// there is a previous ship here (horizontally)
							legit = 0;
						}
					}
				}
			}
			if (rotation_mark == 1 && legit == 1){
				for (int i = 0; i < 10; i++){
					for (int j = 0; j < eng_num; j++){
						if (board[y_rand+j-1][x_rand-1] == 1){	// there is a previous ship here (vertically)
							legit = 0;
						}
					}
				}
			}

			double distance = 0;
		
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					if (board[j][i] == 1){
						int ygr = j+1;
						int xgr = i+1;
						Point point;
						point.x = xgr; point.y = ygr;
						push(&valid, point); //saving current boats
					}
				}
			}

			if (rotation_mark == 0 && legit == 1){
				for (int i = 0; i < valid.size; i++){
					for (int j = 0; j < eng_num; j++){
						int x1 = x_rand + j, x2 = valid.pt[i].x;
						int y1 = y_rand, y2 = valid.pt[i].y;
						distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
						if (distance < 1.5){
							legit = 0;
						}
					}
				}
			}
			if (rotation_mark == 1 && legit == 1){
				for (int i = 0; i < valid.size; i++){
					for (int j = 0; j < eng_num; j++){
						int x1 = x_rand, x2 = valid.pt[i].x;
						int y1 = y_rand + j, y2 = valid.pt[i].y;
						distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
						if (distance < 1.5){
							legit = 0;
						}
					}
				}
			}
		
			if (rotation_mark == 0 && legit == 1){
				for (int i = 0; i < eng_num; i++){
					board[y_rand-1][x_rand+i-1] = 1;
				}		
				if (eng_num == 3 && threeship == 1){
					eng_num--;
					threeship--;
					continue;
				}
				if (eng_num == 3 && threeship == 2){
					threeship--;
				}
				if (eng_num != 3){
					eng_num--;
				}
			}
			if (rotation_mark == 1 && legit == 1){
				for (int i = 0; i < eng_num; i++){
					board[y_rand+i-1][x_rand-1] = 1;
				}			
				if (eng_num == 3 && threeship == 1){
					eng_num--;
					threeship--;
					continue;
				}
				if (eng_num == 3 && threeship == 2){
					threeship--;
				}
				if (eng_num != 3){
					eng_num--;
				}
			}
			if (eng_num - 1 < 1){
				return 1;
			}
		}
		if (gameStyle == 1){
			int legit = 1;
			int x_rand = 1+rand()%width;
			int y_rand = 1+rand()%heigth;

			if (board[y_rand-1][x_rand-1] == 1){	// there is a previous ship here
				legit = 0;
			}
		
			if (legit == 1){
				board[y_rand-1][x_rand-1] = 1;
				engineCount--;
			}
			if (engineCount - 1 < 0){
				return 1;
			}
		}
	}
}
int my_gameMP (int **plShip, int **plShot, int **aiShip, int **aiShot, int turnMark, int gameStyle, int width, int heigth){
	int cursx = 1, cursy = 1, player_priv = 1, player2_priv = 0, savedQuit = 0, goHome = 0;
	if (plShip==NULL || plShot==NULL || aiShip==NULL || aiShot==NULL || turnMark<0 || turnMark>1 || gameStyle<0 || gameStyle>1 || width<0 || heigth<0 || width>20 || heigth>10){
		return -2;
	}
	if (turnMark == 1){
		player_priv = 1;
		player2_priv = 0;
	}
	if (turnMark == 0){
		player2_priv = 1;
		player_priv = 0;
	}
	while(1){
		grid_t(width,heigth);
		
		con_set_color(0,7);
		con_set_pos(41,2);
		printf(" ");
		con_set_pos(41,3);
		printf(" ");

		if (player_priv){
			con_set_color(2,0);
			con_set_pos(41,2);
			printf(" ");
			con_set_color(0,2);
			con_set_pos(42,2);
			printf("  P1 turn\n");
		}
		if (player_priv == 0){
			con_set_color(2,0);
			con_set_pos(41,3);
			printf(" ");
			con_set_color(0,1);
			con_set_pos(42,2);
			printf("  P1 turn\n");
		}
		if (player2_priv){
			con_set_color(0,2);
			con_set_pos(42,3);
			printf("  P2 turn\n");
		}
		if (player2_priv == 0){
			con_set_color(0,1);
			con_set_pos(42,3);
			printf("  P2 turn\n");
		}
		con_set_color(0,7);
		
		int x_place = (cursx - 1)*3 + 2;
		int y_place = (cursy - 1)*2 + 2;
		int key = 0;

		if (player_priv){
			printBoards(plShip, plShot, width, heigth);
		}
		int endCheck = 1;
		if (player_priv){
			for (int i = 0; i < heigth; i++){
				for (int j = 0; j < width; j++){
					if (aiShip[i][j] == 1){
						endCheck = 0;
					}
				}
			}
			if (endCheck){
				return 1;   /// PLAYER_1 WON THE GAME //
			}
			con_set_pos(x_place, y_place);
			con_set_color(0,1);
			printf("**");
			con_set_color(0,7);
		
			while (key = con_read_key()){
      			if (key == 'w'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
				if (cursy > 1){
					cursy--;
				}
      			} else if (key == 's'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if ((cursy + 1)<=heigth){
						cursy++;
					}
      			} else if (key == 'a'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if (cursx > 1){
						cursx--;
					}
      			} else if (key == 'd'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if ((cursx + 1)<=width){
						cursx++;
					}
      			} else if (key == 'p'){
					if (plShot[cursy-1][cursx-1] == 0){
						plShot[cursy-1][cursx-1] = 1;
					}
					if (aiShip[cursy-1][cursx-1] == 1){
						plShot[cursy-1][cursx-1] = -1;
						aiShip[cursy-1][cursx-1] = -1;
						player_priv = 1;
						player2_priv = 0;
					}
					else{
						player_priv = 0;
						player2_priv = 1;
						con_clear();
					}
				}
				else if (key == 'q'){
					int	save_status = saveScr(plShip, plShot, aiShip, aiShot, 2, 1, gameStyle, width, heigth);//2 = MP, 1 = p1 turn
					if (save_status == 1){
						savedQuit = 1;
					}
					if (save_status == 0){
						goHome = 1;
					}
      			}
			}
		}
		if (savedQuit == 1 || goHome == 1){
			return 2; // PLAYER SAVED THE GAME OR ATTEMPTED TO - quit anyway//
		}
		
		if (player2_priv){
			printBoards(aiShip, aiShot, width, heigth);
		}

		if (player2_priv){
			con_set_color(0,1);
			con_set_pos(42,2);
			printf("  P1 turn\n");
			con_set_color(0,7);
			con_set_color(0,2);
			con_set_pos(42,3);
			printf("  P2 turn\n");
			con_set_color(0,7);

			endCheck = 1;
			for (int i = 0; i < heigth; i++){
				for (int j = 0; j < width; j++){
					if (plShip[i][j] == 1){
						endCheck = 0; // if player_1 got defeated, exit game with breaker value as 1
					}
				}
			}
			if (endCheck){
				return 0;			// PLAYER_1 LOST THE GAME //
			}
			con_set_pos(x_place, y_place);
			con_set_color(0,1);
			printf("**");
			con_set_color(0,7);
		
			while (key = con_read_key()){
      			if (key == 'w'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if (cursy > 1){
						cursy--;
					}
      			} else if (key == 's'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if ((cursy + 1)<=heigth){
						cursy++;
					}
      			} else if (key == 'a'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if (cursx > 1){
						cursx--;
					}
      			} else if (key == 'd'){
					for (int i = 0; i < (width*3)+2 ;i++){
						for (int j = 0; j < (heigth*2)+2; j++){
							con_set_pos(i, j);printf("  ");
						}
					}
					if ((cursx + 1)<=width){
						cursx++;
					}
      			} else if (key == 'p'){
					if (aiShot[cursy-1][cursx-1] == 0){
						aiShot[cursy-1][cursx-1] = 1;
					}
					if (plShip[cursy-1][cursx-1] == 1){
						aiShot[cursy-1][cursx-1] = -1;
						plShip[cursy-1][cursx-1] = -1;
						player2_priv = 1;
						player_priv = 0;
					}
					else{
						player2_priv = 0;
						player_priv = 1;
						con_clear();
					}
				}
				else if (key == 'q'){
       				int	save_status = saveScr(plShip, plShot, aiShip, aiShot, 2, 0, gameStyle, width, heigth);//2 = MP, 0 = p2 turn
					if (save_status == 1){
						savedQuit = 1;
					}
					if (save_status == 0){
						goHome = 1;
					}
      			}
			}
		}
		if (savedQuit == 1 || goHome == 1){
			return 2; // PLAYER SAVED THE GAME OR ATTEMPTED TO - quit anyway//
		}
		fflush(stdout);	
	}
}
int my_loadFromFile (int **plShip, int **plShot, int **aiShip, int **aiShot, char *filename, int *turnMark, int *gameStyle, int *width, int *heigth){
	if (plShip==NULL || plShot==NULL || aiShip==NULL || aiShot==NULL || filename==NULL || turnMark==NULL || gameStyle==NULL || width==NULL || heigth==NULL){
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

			plShip = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				plShip[i] = malloc(sizeof(int)*10);
			}
			plShot = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				plShot[i] = malloc(sizeof(int)*10);
			}
			aiShip = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				aiShip[i] = malloc(sizeof(int)*10);
			}
			aiShot = malloc(sizeof(int*)*10);
			for (int i = 0; i < 10; i++){
				aiShot[i] = malloc(sizeof(int)*10);
			}
			
			/**fread(plShip, sizeof(int*), 10, fl);
			for (int i = 0; i < 10; i++){
				fread(plShip[i], sizeof(int), 10, fl);
			}
			fread(plShot, sizeof(int*), 10, fl);
			for (int i = 0; i < 10; i++){
				fread(plShot[i], sizeof(int), 10, fl);
			}
			fread(aiShip, sizeof(int*), 10, fl);
			for (int i = 0; i < 10; i++){
				fread(aiShip[i], sizeof(int), 10, fl);
			}
			fread(aiShot, sizeof(int*), 10, fl);
			for (int i = 0; i < 10; i++){
				fread(aiShot[i], sizeof(int), 10, fl);
			}**/
			char trash;
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					fscanf(fl,"%[1]d%[1]c",plShip[j][i],&trash);
				}
			}
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					fscanf(fl,"%[1]d%[1]c",plShot[j][i],&trash);
				}
			}
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					fscanf(fl,"%[1]d%[1]c",aiShip[j][i],&trash);
				}
			}
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 10; j++){
					fscanf(fl,"%[1]d%[1]c",aiShot[j][i],&trash);
				}
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

			plShip = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				plShip[i] = malloc(sizeof(int)*(*width));
			}
			plShot = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				plShot[i] = malloc(sizeof(int)*(*width));
			}
			aiShip = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				aiShip[i] = malloc(sizeof(int)*(*width));
			}
			aiShot = malloc(sizeof(int*)*(*heigth));
			for (int i = 0; i < *heigth; i++){
				aiShot[i] = malloc(sizeof(int)*(*width));
			}

			fread(plShip, sizeof(int), (*width)*(*heigth), fl);
			fread(plShot, sizeof(int), (*width)*(*heigth), fl);
			fread(aiShip, sizeof(int), (*width)*(*heigth), fl);
			fread(aiShot, sizeof(int), (*width)*(*heigth), fl);
			fclose(fl);
			return modeId;
		}
	}
	else {
		return -1;
	}
}


int main (){
	int **array, turnMark, style, width, heigth;
	assert(my_setScr(-1,-1,NULL,-1,-1,-1,-1) == 0);
	assert(my_setScr(10,10,array,1,9,9,2) == 0);
	assert(my_setScr(1,1,array,0,5,5,0) == 0);

	assert(my_saveScr(NULL,NULL,NULL,NULL,-1,-1,-1,-1,-1) == 0);
	assert(my_saveScr(array,array,array,array,1,0,0,1,1) == 0);
	assert(my_saveScr(array,array,array,array,2,1,0,-1,1) == 0);

	assert(my_game(NULL,NULL,NULL,NULL,-1,-1,-1) == -1);
	assert(my_game(array,array,array,array,1,10,10) == -1);
	assert(my_game(array,array,array,array,0,30,5) == -1);

	assert(my_aiSet(NULL,-1,-1,-1,0) == 0);
	assert(my_aiSet(NULL,1,5,5,5) == 0);
	assert(my_aiSet(array,1,10,10,1) == 0);

	assert(my_gameMP(NULL,NULL,NULL,NULL,-1,-1,-1,-1) == -2);
	assert(my_gameMP(array,array,array,array,1,0,10,10) == -2);
	assert(my_gameMP(NULL,array,array,array,0,1,5,5) == -2);

	assert(my_loadFromFile(array,array,array,array,NULL,&turnMark,&style,&width,&heigth) == -1);
	assert(my_loadFromFile(array,array,array,array,"save_1.txt",&turnMark,&style,&width,&heigth) == -1);
	assert(my_loadFromFile(NULL,NULL,NULL,NULL,"save_1.txt",&turnMark,&style,&width,&heigth) == -1);
	return 0;
}/**
int setScr (int cursx, int cursy, int **plShip, int gameStyle, int width, int heigth, int engineCount);
int saveScr (int **plShip, int **plShot, int **aiShip, int **aiShot, int modeId, int turnMark, int gameStyle, int width, int heigth);
int game (int **aiShip, int **aiShot, int **plShip, int **plShot, int gameStyle, int width, int heigth);
int aiSet (int **board, int gameStyle, int width, int heigth, int engineCount);
int gameMP (int **plShip, int **plShot, int **aiShip, int **aiShot, int turnMark, int gameStyle, int width, int heigth);
int loadFromFile (int **plShip, int **plShot, int **aiShip, int **aiShot, char *filename, int *turnMark, int *gameStyle, int *width, int *heigth);
**/
