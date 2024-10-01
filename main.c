#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int main()
{
    //Variables

    //Fill the table for better view
    for(int k = 0; k < 9; k++){
        for(int s = 0; s < 9; s++){
            tictactoe[k][s] = '-';
        }
    }

    //Random int for choose who begins
    srand(time(NULL));
    int r = rand() % 2;

    Tgamemanager gamemanager;
    gamemanager.lastPos = -1;

    //gameloop
    while(1){
        //Enter here if is the fist play
        if (gamemanager.lastPos == -1){
            jogada(&gamemanager, r, 1);
        }

        //Checks if the last choosed small tictactoe is completed, if not: runs
        else if (checkComplete(gamemanager.lastPos2 - 1, tictactoe) == 0){
            jogada(&gamemanager, gamemanager.nextPlayer, 0);
        }

        //Gives the player oportunity to choose where will play in the big tictactoe
        else{
            jogada(&gamemanager, gamemanager.nextPlayer, 1);
        }

        //Check if the big tic tac toe is winned

        for(int i = 0; i < 9; i++){
            gamemanager.winned[i] = checkWinner(tictactoe, i);
        }

        if(checkBigWinner(gamemanager.winned)!= '-'){
            if(gamemanager.lastPlayer == 0){
                printf("The \"O\" is the winner!\n");
                break;
            }
            else if (gamemanager.lastPlayer == 1){
                printf("The \"X\" is the winner!\n");
                break;
            }
            else{
                printf("It's a draw!\n");
                break;
            }

        }
    }

}
