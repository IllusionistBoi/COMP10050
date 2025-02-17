/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <string.h>


/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
 
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){

    int i,j;
	for ( i =0; i< NUM_ROWS; i++){
        for(j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7) Points
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4)
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } 
			else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack_top = NULL;
        }
    }
}

/* Initialising the color to the number using switch case */

enum color get_player_color(int i) {
  enum color col;
  switch(i) {
      case 0: col =  RED;
              break;
      case 1: col = BLU;
              break;
      case 2: col = GREEN;
              break;
      case 3: col = YELLOW;
              break;
      case 4: col = PINK;
              break;
      case 5: col = ORANGE;
              break;
      default: break;
  }
  return col;
}


 /*
	 * This function creates players for the first time
	 *
	 * Input: the array of players to be initialized
	 * Output: The number of players of the game
 */
 
int initialize_players(player players[]) {
    int numOfPlayers;
    enum color col;

    char name[20];

    /*	*/
    Again :
	printf("\n How Many Players Will Play The Game [2:6] :) ");
    scanf("%d",&numOfPlayers);
    
    /*It checks if the player entered by user is within the rule for the game Min-2 Max-6*/
    if(numOfPlayers<2 || numOfPlayers>6)
    	goto Again;
    
	int i;
	for(i=0; i<numOfPlayers; i++) {
      printf("\nEnter The Details Of Player %d:",i+1);
      printf("\nName : ");
      scanf("%s", name);
      strcpy(players[i].name, name);
      col = get_player_color(i);
      printf("Color %d\n", i);
      players[i].col = col;
    }
    return numOfPlayers;
}
