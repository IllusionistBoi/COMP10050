/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 *
 *
 *
 * File:   main.c
 * Author: Ronit Dahiya
 *
 * Created on 07 April 2019, 12:11
 */

#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
	
	// To Randomise the Roll Dice 
	srand(time(NULL));
    
	//The board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];

    //An array containing the players (MAX 6 players)
    player players[6];

    //The number of players
    int numPlayers =0;

    //Creates the squares of the board
    initialize_board(board);

    //Prints the board
    print_board(board);

    //Creates the players
    numPlayers = initialize_players(players);

    /*Asks each player to place their tokens
    On the first column of the board*/
    
    place_tokens(board, players, numPlayers);

    //Lets Start The Game
    printf("\n------------Starting the game----------\n ");
   
    //Manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);

    return 0;
 }
