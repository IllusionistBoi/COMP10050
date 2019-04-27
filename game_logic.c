/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>

void printLine();
/*
 * Returns the first letter associated with the color of the token
 *
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 *
 */
 
	 char print_token(token *t) {
	    if((*t).col== PINK)   return 'P';
	    if((*t).col== RED)    return 'R';
	    if((*t).col== BLU)    return 'B';
	    if((*t).col== GREEN)  return 'G';
	    if((*t).col== ORANGE) return 'O';
	    if((*t).col== YELLOW) return 'Y';
	    return '\0';
	}

	char print_player_col(player p) {
	  if((p).col== PINK)     return 'P';
	  if((p).col== RED)      return 'R';
	  if((p).col== BLU)      return 'B';
	  if((p).col== GREEN)    return 'G';
	  if((p).col== ORANGE)   return 'O';
	  if((p).col== YELLOW)   return 'Y';
	  return '\0';
	}

/*
 * Prints the board
 *
 * Input: the board to be printed.
 *
 */
 
	void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
	    printf("                THE BOARD\n");
	    
		int i,j;
		for(i =0; i < NUM_ROWS; i++) {
	
	        //prints an horizontal line
	        printLine();
	        //prints the row number
	        printf(" %d ", i);
	        char c = '\0' ;
	        //if the square (i,j) is occupied,
	        //c is assigned the initial of the color of the token that occupies the square
	              for (j = 0; j < NUM_COLUMNS; j++) {
		            	if(board[i][j].stack_top != NULL){
		                  c = print_token(board[i][j].stack_top);
	            	    }
	        /* if the square (i,j) is empty */
	                    else{
		    /* c is assigned 'X' if the square represents an obstacle */
			                if(board[i][j].type == OBSTACLE)
			                    c = 'X';
			/* c is assigned an empty space otherwise */
			                else c = ' ';
	            		}
	                    printf("| %c ", c);
	        		}
	        printf ("|\n");
	    }
	    
		printLine();
	/* prints the number of the columns at the end of the board */
	    printf("     0   1   2   3   4   5   6   7   8\n");
	}

	void printLine(){
	  printf("   -------------------------------------\n");
	}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
    int minNumOfTokens = 0;
    int selectedRow = 0;
    int selectedCol = 0;

    int i,j;
	for(i=0; i<4 ; i++) {
      for( j=0; j< numPlayers; j++) {
        cont:
        do {
          printf("\nPlayer %d please select a square: ", j+1);
          scanf("%d", &selectedRow);
        } while(selectedRow > 5 || selectedRow < 0);
        
        // This case arises when the selected square has no token.
        // Pushing the new token with same color as players to the stack_top of the square;
        if(board[selectedRow][0].stack_top == NULL) {
          token *temp = (token*)malloc(sizeof(token));
          temp -> col = players[j].col;
          temp -> next = NULL;
          board[selectedRow][0].stack_top = temp;
          board[selectedRow][0].numTokens++;
          
        }
        
		// Condition to be checked whether the selected square has minimum # of token and is color of the player's token and 
        // token at the stack_top of square is not same.
        // If both these conditions satisfy, then we push new token t to the stack of square.
        else if( board[selectedRow][0].numTokens == minNumOfTokens && board[selectedRow][0].stack_top -> col != players[j].col) {
          token *t = (token*)malloc(sizeof(token));
          t->next = board[selectedRow][0].stack_top;
          t->col = players[j].col;
          board[selectedRow][0].stack_top = t;
          board[selectedRow][0].numTokens++;
          
        }
        
		// When above 3 conditions doesn't comply, then will ask user again and again.
        else {
          goto cont;
        }
		
		//prints board after every token placement
		print_board(board);

        if(((numPlayers * i)+ j + 1)%NUM_ROWS == 0)
          minNumOfTokens++;
      }
    }
}

/*
 * Play game and move tokens from first column to other columns
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
*/

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
  // Steps to play the game for every players
  // 1. Roll the dice.
  // 2. Sidestep one of your pieces (i.e can move to a row below or above the piece and stack on top of that board)
  // 3. Move a piece from that numbered rolled from dice by 1 space (mandatory)

  // Condition to win
  // When 3 out of 4 tokens of a player are in last column then that player wins

  // Obstacle Squares Conditions
  // When a token is stuck at an Obstacle square then it has to wait for other tokens to catch upto the same column. Then it can again move!

  //variables for loops
  
  int i,j,k,l; 
  int won = 0;
  
  // Infinite Loop until one of the player wins
  while (!won) {
    // Loop for each player
    for(i=0 ; i<numPlayers; i++) {

      int colFull = 1;

      printf("\n\nPlayer %s turn with color %c.", players[i].name, print_player_col(players[i]));
  
      // 1. Roll the dice
      int lucky = (rand() %  (5 - 0 + 1)) + 0;
      printf("\nRolling Dice and your Lucky number is: %d\n", lucky );

      // 2.  Sidestep one of players pieces (optional) i.e move any of players piece that is at top of the stack either below or above the row
      int c = 0;
      int sRow, sCol,dir=-1;
      
      printf("\nDo you wanna sidestep one of your piece :\nPress 1 for Yes \n Press 0 for No");
      scanf("%d",&c);
      
	  if(c == 1) {
        printf("\nEnter the row and column of the piece to be sidestepped and direction (0->Up and 1->Down):\nFor example. if you want to move the token in first row,second coloum and move it UP then you enter : 1 2 0 or 1 2 1 if you want to move token down.\n ");
        scanf("%d %d %d",&sRow,&sCol,&dir);

        // Since we are gonna move the token from stack of selected sRow and sCol to different column on basis of dir variable
        // Steps to pop out the token from sRow and sCol squre.
        token *st = board[sRow][sCol].stack_top;
        board[sRow][sCol].stack_top = board[sRow][sCol].stack_top->next;


        // Validation not done on dir
        // Pushing the poped token to new square stack top according to dir.
        if(dir == 0) {
          st -> next = board[sRow-1][sCol].stack_top;
          board[sRow-1][sCol].stack_top = st;
        } 
		
		else if(dir == 1) {
          st -> next = board[sRow+1][sCol].stack_top;
          board[sRow+1][sCol].stack_top = st;
        }
      } 
	  
	  else {
        printf("\nNo Sidestep took!\n");
      }

      // 3. Move a piece from that numbered rolled from dice by 1 space (mandatory)
      // To get the column of the token which needs to be moved.
      int moveCol = -1;
      for(k=0; k< NUM_COLUMNS; k++) {
        if(board[lucky][k].stack_top != NULL) {
          moveCol = k;
        }
      }

      // Token is being moved from one square to another (Obstacles case included too!).

      // Case 1. When the square selected by roll of dice is not an obstacle
      if(board[lucky][moveCol].type != OBSTACLE) {

        // Poping the token from selected column
        token *t = board[lucky][moveCol].stack_top;
        board[lucky][moveCol].stack_top = board[lucky][moveCol].stack_top -> next;
        moveCol++;

        // Pushing it to adjacent column (mandatory)
        t -> next = board[lucky][moveCol].stack_top;
        board[lucky][moveCol].stack_top = t;
        
      } 
     
	  // Obstacle Case 
      else {
        // Checking if whole column is full or not 
        for(l=0; l<NUM_ROWS; l++) {
          if(board[l][moveCol].stack_top == NULL) {
            colFull = 0;
            break;
          }
        }

        // If column is full then we move the obstacle token
        // else we dont.
        if(colFull) {
          token *t = board[lucky][moveCol].stack_top;
          board[lucky][moveCol].stack_top = board[lucky][moveCol].stack_top -> next;
          t->next = NULL;
          moveCol++;
          board[lucky][moveCol].stack_top = t;
        } 
		
		else {
          printf("\nSorry token is on Obstacle and can't move ahead!!!");
        }
      }
      
      // After moving the pieces, show the board again.
      print_board(board);

      // Check in last column, whether player has gotten a token then increment numTokensLastCol by 1
      for(l=0; l < NUM_ROWS; l++) {
        if( board[l][NUM_COLUMNS-1].stack_top != NULL && board[l][NUM_COLUMNS-1].stack_top ->col == players[i].col) {
          players[i].numTokensLastCol += 1;
        }
      }

      // Checking if player has more than 3 tokens on Last column then player won.
      if(players[i].numTokensLastCol >=3) {
        printf("\nPlayer %s won!!!!!", players[i].name);
        won = 1;
        break;
      }
    }
  }
}
