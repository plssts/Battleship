#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "con_lib.h"
#include "save_load.h"
#include "score.h"
typedef struct{
	int x, y;
}Point;
typedef struct{
	Point *pt;
	int size;
}Stack;
void seeTime (){
	FILE *fo = fopen("log.txt","rb");
	time_t start, end;
	time(&end);
	fseek(fo,-sizeof(time_t),SEEK_END);
	fread(&start,sizeof(time_t),1,fo);
	fclose(fo);
	double diff = difftime(end,start);
	FILE *flog = fopen("log.txt","a");
	fprintf(fo,"Execution time: %lf s\n\n",diff);
	fclose(fo);
}
void changePl (){
	con_clear();
	for (int i = 5; i > 0; i--){
		con_set_color(0,1);
		con_set_pos(4,5);
		printf("Allow next player to make his shot\n");
		con_set_pos(10,7);
		con_set_color(2,0);
		if (i <= 3){
			con_set_color(1,0);
		}
		printf("%i\n",i);
		con_sleep(1);
	}	
}
void grid_t(int x, int y){
	for (int i = 1; i < (y*2)+2; i=i+2){
    	for (int j = 1; j < (x*3)+2; j++){
			con_set_pos(j, i);
    		printf("-");
		}
	}
 	for (int i = 2; i < (y*2)+2; i=i+2) {
    		for (int j =1; j < (x*3)+3; j=j+3){
				con_set_pos(j, i);
				printf("|");
			}
  	}

	char *rd[20] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","R","S","T","U"};
	int ind=0;
	for (int i = 2; i < x*3; i=i+3){
		con_set_pos(i, (y*2)+2);
		printf("%c",*rd[ind++]);
	}
	int sk[10] = {1,2,3,4,5,6,7,8,9,10};
	int ID = 0;
	for (int i = 2; i< (y*2)+2; i=i+2){
		con_set_pos((x*3)+3, i);
		printf("%i",sk[ID++]);
	}
	fflush(stdout);
}
void grid (){
	for (int i = 1; i < 22; i=i+2){
    	for (int j = 1; j< 32; j++){
			con_set_pos(j, i);
    		printf("-");
		}
	}
 	for (int i = 2; i < 22; i=i+2) {
    		for (int j =1; j < 32; j=j+3){
				con_set_pos(j, i);
				printf("|");
			}
  	}

	//Without gridlines
	/**
	for (int i = 2; i < 32 ; i++){
		con_set_pos(i, 1);printf("-");
		con_set_pos(i, 21);printf("-");
	}
	for (int i = 1; i< 11; i++){
		con_set_pos(1, i);printf("|");
		con_set_pos(32, i);printf("|");
	}**/

	char *rd[10] = {"A","B","C","D","E","F","G","H","I","J"};
	int ind=0;
	for (int i = 2; i < 30; i=i+3){
		con_set_pos(i, 22);
		printf("%c",*rd[ind++]);
	}
	int sk[10] = {1,2,3,4,5,6,7,8,9,10};
	int ID = 0;
	for (int i = 2; i< 22; i=i+2){
		con_set_pos(33, i);
		printf("%i",sk[ID++]);
	}
	fflush(stdout);
}
void push (Stack *stack, Point pt){
	Point *oldarr = stack->pt;
	stack->pt = malloc(sizeof(Point)*(stack->size+1));
	for (int i = 0; i < stack->size ; i++){
		stack->pt[i] = oldarr[i];
	}
	stack->pt[stack->size] = pt;
	stack->size++;
	free(oldarr);
}
void printBoards (int **playerShip, int **playerShot, int width, int heigth){
	for (int i = 0; i < heigth; i++){
		for (int j = 0; j < width; j++){
			if (playerShip[i][j] == 1){
				int cursx = j+1;
				int cursy = i+1;
				int x_place = (cursx - 1)*3 + 2;
				int y_place = (cursy - 1)*2 + 2;
				con_set_color(2,0);
				con_set_pos(x_place, y_place);
				printf("  ");
			}
			if (playerShip[i][j] == -1){
				int cursx = j+1; 
				int cursy = i+1;
				int x_place = (cursx - 1)*3 + 2;
				int y_place = (cursy - 1)*2 + 2;
				con_set_color(1,0);
				con_set_pos(x_place, y_place);
				printf("  ");
			}
		}
	}
	con_set_color(0,7);
	for (int i = 0; i < heigth; i++){
		for (int j = 0; j < width; j++){
			if (playerShot[i][j] == 1){
				if (playerShot[i][j] == playerShip[i][j]){
					int cursx = j+1; 
					int cursy = i+1;
					int x_place = (cursx - 1)*3 + 2;
					int y_place = (cursy - 1)*2 + 2;
					con_set_color(2,0);
					con_set_pos(x_place, y_place);//pakitimas: x_place+1 ir "*" keista i x_place ir "**"
					printf("**");
				} 
				else if (playerShip[i][j] == -1){
					int cursx = j+1; 
					int cursy = i+1;
					int x_place = (cursx - 1)*3 + 2;
					int y_place = (cursy - 1)*2 + 2;
					con_set_color(1,0);
					con_set_pos(x_place, y_place);//pakitimas: x_place+1 ir "*" keista i x_place ir "**"
					printf("**");
				}
				else{
					int cursx = j+1; 
					int cursy = i+1;
					int x_place = (cursx - 1)*3 + 2;
					int y_place = (cursy - 1)*2 + 2;
					con_set_color(0,7);
					con_set_pos(x_place, y_place);//pakitimas: x_place+1 ir "*" keista i x_place ir "**"
					printf("**");
				}
			}
			if (playerShot[i][j] == -1){
				int cursx = j+1; 
				int cursy = i+1;
				int x_place = (cursx - 1)*3 + 2;
				int y_place = (cursy - 1)*2 + 2;
				con_set_color(6,0);
				con_set_pos(x_place+1, y_place);
				printf("#");
			}
		}
	}
	con_set_color(0,7);
	fflush(stdout);
}
void printShips (int **board, int width, int heigth){
	con_set_color(2,0);
	for (int i = 0; i < heigth; i++){
		for (int j = 0; j < width; j++){
			if (board[i][j] == 1){
				int cursx = j+1; 
				int cursy = i+1;
				int x_place = (cursx - 1)*3 + 2;
				int y_place = (cursy - 1)*2 + 2;
				con_set_pos(x_place, y_place);
				printf("  ");
			}
		}
	}
	fflush(stdout);
	con_set_color(0,7);
}
void initStack (Stack *stack){
	stack->pt = 0; 
	stack->size = 0;
}
int setScr (int cursx, int cursy, int **plShip, int gameStyle, int width, int heigth, int engineCount){
	int rotation_mark = 0, eng_num = 5;
	int threeship = 2;
	if (1/**cursx>width || cursy>heigth || cursx<0 || cursy<0 || gameStyle<0 || gameStyle>1 || width<0 || heigth<0 || width>20 || heigth>10 || engineCount<1 || engineCount>(width*heigth)/3**/){
		//return 0;
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
void rembrd (Boards *bd, int width){
	for (int i = 0; i < width; i++){
		if (bd->plShip[i]!= NULL){
			free(bd->plShip[i]);
		}
		if (bd->plShot[i]!= NULL){
			free(bd->plShot[i]);
		}
		if (bd->aiShip[i]!= NULL){
			free(bd->aiShip[i]);
		}
		if (bd->aiShot[i]!= NULL){
			free(bd->aiShot[i]);
		}
	}
	if (bd->aiShot!= NULL){
		free(bd->plShip);	
	}
	if (bd->aiShip!= NULL){
		free(bd->plShot);
	}
	if (bd->plShot!= NULL){
		free(bd->aiShip);	
	}
	if (bd->plShip!= NULL){
		free(bd->aiShot);
	}
}
void rmsingl (int **board){
	for (int i = 0; i < 10; i++){
		free(board[i]);
	}	
	free(board);
}
int saveScr (int **plShip, int **plShot, int **aiShip, int **aiShot, int modeId, int turnMark, int gameStyle, int width, int heigth){
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
int homeScr (){
	while(1){
		con_clear();
		con_sleep(0.09);

		/** B **/
		con_set_pos(16,4);
		con_set_color(0, 1+rand()%6);
		printf("_");
		con_set_pos(17,4);
		printf("_");
		con_set_pos(15,5);
		printf("|");
		con_set_pos(18,5);
		printf("\\");
		con_set_pos(15,6);
		printf("|");
		con_set_pos(18,6);
		printf("/");
		con_set_pos(17,6);
		printf("_");
		con_set_pos(16,6);
		printf("_");
		con_set_pos(15,7);
		printf("|");
		con_set_pos(18,7);
		printf("\\");
		con_set_pos(15,8);
		printf("|");
		con_set_pos(16,8);
		printf("_");
		con_set_pos(17,8);
		printf("_");
		con_set_pos(18,8);
		printf("/");

		/** A **/
		con_set_pos(21,4);
		con_set_color(0, 1+rand()%6);
		printf("_");
		con_set_pos(22,4);
		printf("_");
		con_set_pos(20,5);
		printf("|");
		con_set_pos(23,5);
		printf("|");
		con_set_pos(20,6);
		printf("|");
		con_set_pos(23,6);
		printf("|");
		con_set_pos(21,6);
		printf("_");
		con_set_pos(22,6);
		printf("_");
		con_set_pos(20,7);
		printf("|");
		con_set_pos(23,7);
		printf("|");
		con_set_pos(20,8);
		printf("|");
		con_set_pos(23,8);
		printf("|");

		/** T **/
		con_set_pos(25,4);
		con_set_color(0, 1+rand()%6);
		printf("_");
		con_set_pos(26,4);
		printf("_");
		con_set_pos(27,4);
		printf("_");
		con_set_pos(28,4);
		printf("_");
		con_set_pos(29,4);
		printf("_");
		con_set_pos(27,5);
		printf("|");
		con_set_pos(27,6);
		printf("|");
		con_set_pos(27,7);
		printf("|");		
		con_set_pos(27,8);
		printf("|");		
		
		/** T **/
		con_set_pos(31,4);
		con_set_color(0, 1+rand()%6);
		printf("_");
		con_set_pos(32,4);
		printf("_");
		con_set_pos(33,4);
		printf("_");
		con_set_pos(34,4);
		printf("_");
		con_set_pos(35,4);
		printf("_");
		con_set_pos(33,5);
		printf("|");
		con_set_pos(33,6);
		printf("|");
		con_set_pos(33,7);
		printf("|");		
		con_set_pos(33,8);
		printf("|");

		/** L **/
		con_set_pos(37,5);
		con_set_color(0, 1+rand()%6);
		printf("|");
		con_set_pos(37,6);
		printf("|");
		con_set_pos(37,7);
		printf("|");
		con_set_pos(37,8);
		printf("|");
		con_set_pos(38,8);
		printf("_");
		con_set_pos(39,8);
		printf("_");
		con_set_pos(40,8);
		printf("_");
		
		/** E **/
		con_set_pos(43,4);
		con_set_color(0, 1+rand()%6);
		printf("_");
		con_set_pos(44,4);
		printf("_");
		con_set_pos(45,4);
		printf("_");
		con_set_pos(42,5);
		printf("|");
		con_set_pos(42,6);
		printf("|");
		con_set_pos(43,6);
		printf("_");
		con_set_pos(44,6);
		printf("_");
		con_set_pos(45,6);
		printf("_");
		con_set_pos(42,7);
		printf("|");
		con_set_pos(42,8);
		printf("|");
		con_set_pos(43,8);
		printf("_");
		con_set_pos(44,8);
		printf("_");
		con_set_pos(45,8);
		printf("_");

		/** S **/
		con_set_pos(47,5);
		con_set_color(0, 1+rand()%6);
		printf("/");
		con_set_pos(48,4);
		printf("_");
		con_set_pos(49,4);
		printf("_");
		con_set_pos(47,6);
		printf("\\");
		con_set_pos(48,6);
		printf("_");
		con_set_pos(49,6);
		printf("_");
		con_set_pos(50,7);
		printf("\\");
		con_set_pos(50,8);
		printf("/");
		con_set_pos(49,8);
		printf("_");
		con_set_pos(48,8);
		printf("_");

		/** H **/
		con_set_pos(52,5);
		con_set_color(0, 1+rand()%6);
		printf("|");
		con_set_pos(52,6);
		printf("|");
		con_set_pos(52,7);
		printf("|");
		con_set_pos(52,8);
		printf("|");
		con_set_pos(55,5);
		printf("|");
		con_set_pos(55,6);
		printf("|");
		con_set_pos(55,7);
		printf("|");
		con_set_pos(55,8);
		printf("|");
		con_set_pos(53,6);
		printf("_");
		con_set_pos(54,6);
		printf("_");

		/** I **/
		con_set_pos(57,8);
		con_set_color(0, 1+rand()%6);
		printf("|");
		con_set_pos(57,7);
		printf("|");
		con_set_pos(57,6);
		printf("|");
		con_set_pos(57,5);
		printf("|");

		/** P **/
		con_set_pos(60,8);
		con_set_color(0, 1+rand()%6);
		printf("|");
		con_set_pos(60,7);
		printf("|");
		con_set_pos(60,6);
		printf("|");
		con_set_pos(60,5);
		printf("|");
		con_set_pos(61,4);
		printf("_");
		con_set_pos(62,4);
		printf("_");
		con_set_pos(63,5);
		printf("\\");
		con_set_pos(63,6);
		printf("/");
		con_set_pos(62,6);
		printf("_");
		con_set_pos(61,6);
		printf("_");
		
		con_set_color(0,7);
		con_set_pos(28,14);
		printf("[1]   New Game   [1]\n");
		con_set_pos(28,15);
		printf("[2]   Load Game  [2]\n");
		con_set_pos(28,16);
		printf("[3] Instructions [3]\n");
		con_set_pos(28,17);
		printf("[4]  Highscores  [4]\n");
		con_set_pos(28,18);
		printf("[5]  Quit Game   [5]\n");
		int key = 0;
		while (key = con_read_key()){
      		if (key == '1'){			
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,14);
				printf("[1]   New Game   [1]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,14);
				printf("[1]   New Game   [1]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,14);
				printf("[1]   New Game   [1]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,14);
				printf("[1]   New Game   [1]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,14);
				printf("[1]   New Game   [1]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,14);
				printf("[1]   New Game   [1]\n");
				return 1;
      		}
			else if (key == '2'){   				
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,15);
				printf("[2]   Load Game  [2]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,15);
				printf("[2]   Load Game  [2]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,15);
				printf("[2]   Load Game  [2]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,15);
				printf("[2]   Load Game  [2]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,15);
				printf("[2]   Load Game  [2]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,15);
				printf("[2]   Load Game  [2]\n");
				return 2;
 			}
			else if (key == '3'){
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,16);
				printf("[3] Instructions [3]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,16);
				printf("[3] Instructions [3]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,16);
				printf("[3] Instructions [3]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,16);
				printf("[3] Instructions [3]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,16);
				printf("[3] Instructions [3]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,16);
				printf("[3] Instructions [3]\n");
				return 3;
			}
			else if (key == '4'){
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,17);
				printf("[4]  Highscores  [4]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,17);
				printf("[4]  Highscores  [4]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,17);
				printf("[4]  Highscores  [4]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,17);
				printf("[4]  Highscores  [4]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,17);
				printf("[4]  Highscores  [4]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,17);
				printf("[4]  Highscores  [4]\n");
				return 4;
			}
			else if (key == '5'){
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,18);
				printf("[5]  Quit Game   [5]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,18);
				printf("[5]  Quit Game   [5]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,18);
				printf("[5]  Quit Game   [5]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,18);
				printf("[5]  Quit Game   [5]\n");
				con_set_color(0,1);
				con_sleep(0.1);
				con_set_pos(28,18);
				printf("[5]  Quit Game   [5]\n");
				con_set_color(0,7);
				con_sleep(0.1);
				con_set_pos(28,18);
				printf("[5]  Quit Game   [5]\n");
				return 5;
			}
		}
	fflush(stdout);
	}
}

int game (int **aiShip, int **aiShot, int **plShip, int **plShot, int gameStyle, int width, int heigth){
	int cursx = 1, cursy = 1, player_priv = 1, ai_priv = 0, last_x = 0, last_y = 0, savedQuit = 0, goHome = 0, playerScore = 0;
	Stack shooting;
	initStack(&shooting); // for storing ai successful shots
	if (aiShip==NULL || aiShot==NULL || plShip==NULL || plShot==NULL || gameStyle<0 || gameStyle>1 || width<0 || heigth<0 || width>20 || heigth>10){
		return -1;
	}
	while(1){
		grid_t(width,heigth);
		fflush(stdout);

		if (player_priv){
			con_set_color(2,0);
			con_set_pos(width+4,2);
			printf(" ");
			con_set_color(0,2);
			con_set_pos(width+5,2);
			printf("  Your turn\n");
		}
		if (player_priv == 0){
			con_set_color(1,0);
			con_set_pos(width+4,2);
			printf(" ");
			con_set_color(0,1);
			con_set_pos(width+5,2);
			printf("  Your turn\n");
		}
fflush(stdout);
		if (ai_priv){
			con_set_color(0,2);
			con_set_pos(width+5,3);
			printf("  PC's turn\n");
		}
		if (ai_priv == 0){
			con_set_color(0,1);
			con_set_pos(width+5,3);
			printf("  PC's turn\n");
		}
		con_set_color(0,7);
fflush(stdout);
		
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
				fflush(stdout);
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

int aiSet (int **board, int gameStyle, int width, int heigth, int engineCount){
	int rotation_mark, eng_num = 5;
	int threeship = 2;

	Stack valid;
	initStack(&valid);
	if (1/**board==NULL || width<0 || heigth<0 || width>20 || heigth>10 || engineCount<1 || engineCount>(width*heigth)/3**/){
		//return 0;
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
void initBoard (int board[10][10]){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			board[i][j] = 0; // jokios reiksmes koordinatese is pradziu neturi buti.
		}
	}
}
void helpScr (){
	int quit = 0;
	while(1){
		int key = 0;
		con_clear();
		con_sleep(0.09);
		printf("Use W, A, S, D to move ships/cursor around the board\n");
		printf("Use Q key to quit any stage of the game, including this screen\n");
		printf("Place a ship/make a shot with P key\n\nMODES\n\n");
		printf("Singlepayer matches you against the computer\nMultiplayer allows you to play with another person\n");
		printf("Classic mode gives you 1x[5], 1x[4], 2x[3], 1x[2]-engined ships\n");
		printf("Free mode lets you play on a predefined board [3;3] - [20;10] with your number of engines\n");
		while (key = con_read_key()){
			if (key == 'q'){
				quit = 1;
			}
		}
		if (quit){
			break;
		}
	fflush(stdout);
	}
}

int gameMP (int **plShip, int **plShot, int **aiShip, int **aiShot, int turnMark, int gameStyle, int width, int heigth){
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
		con_set_pos(3*width+4,2);
		printf(" ");
		con_set_pos(3*width+5,3);
		printf(" ");

		if (player_priv){
			con_set_color(2,0);
			con_set_pos(3*width+4,2);
			printf(" ");
			con_set_color(0,2);
			con_set_pos(3*width+5,2);
			printf("  P1 turn\n");
		}
		if (player_priv == 0){
			con_set_color(2,0);
			con_set_pos(3*width+4,3);
			printf(" ");
			con_set_color(0,1);
			con_set_pos(3*width+5,2);
			printf("  P1 turn\n");
		}
//fflush(stdout);
		if (player2_priv){
			con_set_color(0,2);
			con_set_pos(3*width+5,3);
			printf("  P2 turn\n");
		}
		if (player2_priv == 0){
			con_set_color(0,1);
			con_set_pos(3*width+5,3);
			printf("  P2 turn\n");
		}
		con_set_color(0,7);
//fflush(stdout);
		
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
						changePl();
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
			/*con_set_color(0,1);
			con_set_pos(42,2);
			printf("  P1 turn\n");
			con_set_color(0,7);
			con_set_color(0,2);
			con_set_pos(42,3);
			printf("  P2 turn\n");
			con_set_color(0,7);*/

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
						changePl();
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
int newScr(){
	while (1){
		con_clear();
		con_sleep(0.09);
		int key = 0;
		printf("1 = SinglePlayer, classic\n2 = MultiPlayer, classic\n3 = SinglePlayer, free\n4 = MultiPlayer, free\n");
		while (key = con_read_key()){
			if (key == '1'){
				con_clear();
				return 1;
			}
			else if (key == '2'){
				con_clear();
				return 2;
			}
			else if (key == '3'){
				con_clear();
				return 3;
			}
			else if (key == '4'){
				con_clear();
				return 4;
			}
		}
	}
}
void nulbrd (Boards *bd){
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
		for (int j = 0; j < 10; j++){
			bd->plShip[i][j] = 0;
			bd->plShot[i][j] = 0;
			bd->aiShip[i][j] = 0;
			bd->aiShot[i][j] = 0;
		}
	}
}
void sizeSelect(int *width, int *heigth, int *engineCount){
	int breakOuter = 0;
	while (1){
		con_clear();
		con_sleep(0.09);
		printf("Enter [width]x[heigth]:\n");
		con_show_echo(1);
		int inputCheck = scanf("%dx%d",width,heigth);
		if (inputCheck == 2 && *heigth <= 10 && *heigth >= 3 && *width <= 20 && *width >= 3){
			while (1){
				con_clear();
				con_sleep(0.09);
				printf("Enter the number of engines [1;%i]:\n",(*width*(*heigth))/3);
				inputCheck = scanf("%i",engineCount);
				if (inputCheck == 1 && *engineCount <= (*width*(*heigth))/3 && *engineCount > 0){
					con_show_echo(0);
					breakOuter = 1;
					break;
				}
				while (getchar()!='\n'){}
			}
		}
		while (getchar()!='\n'){}
		if (breakOuter){
			con_clear();
			break;
		}
	}
}

