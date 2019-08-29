/*
Author: Paulius Staisiunas. 2016
*/

#include "func.h"
#include "con_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort (List *data, int n, int criteria){
	while(1){
		int swapd = 0;
		for (int i = 0; i < n-1; i++){
			if (criteria == 1){
				if (strcmp(data->name[i],data->name[i+1]) > 0){
					char temp[21];
					strcpy(temp,data->name[i]);
					strcpy(data->name[i],data->name[i+1]);
					strcpy(data->name[i+1],temp);
					int tp = data->score[i];
					data->score[i] = data->score[i+1];
					data->score[i+1] = tp;
					swapd = 1;
				}
			}
			if (criteria == 2){
				if (data->score[i] < data->score[i+1]){
					char temp[21];
					strcpy(temp,data->name[i]);
					strcpy(data->name[i],data->name[i+1]);
					strcpy(data->name[i+1],temp);
					int tp = data->score[i];
					data->score[i] = data->score[i+1];
					data->score[i+1] = tp;
					swapd = 1;
				}
			}
		}
		if (swapd == 0){break;}	
	}
}
void scoreLoad (){
	List lst;
	FILE *fo = fopen ("scores.txt","r");
	int size = 0, ID = 0;
	while (!feof(fo)){
		char store[21]; int score;
		fscanf(fo,"%s with score: %i",store,&score);
		strcpy(lst.name[ID],store);
		lst.score[ID] = score;
		size++;
		ID++;
		if (ID == 50){
			break;
		}
	}
	fclose(fo);
	int breakOuter = 0;
	while (1){
		con_clear();
		con_sleep(0.09);
		printf("Leaderboard:\n");
		for (int i = 0; i < size-1 && i < 20; i++){
			printf("[%i]%s : %i\n",i+1,lst.name[i],lst.score[i]);
		}
		printf("\nPress 'n' to change sorting by name\nPress 's' to change sorting by score\n");
		int key = 0;
		while (key = con_read_key()){
			if (key == 'q'){
				breakOuter = 1;
				break;
			}
			else if (key == 'n'){
				sort(&lst,size-1,1);
			}
			else if (key == 's'){
				sort(&lst,size-1,2);
			} 
		}
		if (breakOuter){
			break;
		}
	}
}
void scoreSave (int score){
	con_clear();
	printf("Your score: %i\n",score);
	printf("Type your name:\n");
	con_show_echo(1);
	char name[21];
	scanf("%20[^\n]",name);
	FILE *fc = fopen ("scores.txt","a");
	fprintf(fc,"%s with score: %i\n",name,score);
	fclose(fc);
	con_show_echo(0);
}
