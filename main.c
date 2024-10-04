#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int main()
{
    //Variables
    int rsp = 0;

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

    do{
        printf("Welcome to the Tic Tac Toe 2!\n\n");
        printf("1. New Game\n2. Continue\n3. How to play\n4. Exit\n");
        scanf(" %d", &rsp);

        switch(rsp){
            case 1:
                printf("Creating the table...\n");
                sleep(1);
                rsp = -1;
                break;

            case 2:
                FILE* save;
                save = fopen("save.tic", "r");
                printf("\nLoading the save\n");

                loadGame(save, &gamemanager, &tictactoe);

                sleep(1);

                rsp = -1;

                break;

            case 3:

                break;

            case 4:
                printf("Bye :D\n");
                return;

            default:
                printf("Could not recognize your option, try again\n");
                break;
        }

        clear();
    } while(rsp != -1);

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
                saveGame(gamemanager, tictactoe);
                break;
            }
            else if (gamemanager.lastPlayer == 1){
                printf("The \"X\" is the winner!\n");
                saveGame(gamemanager, tictactoe);
                break;
            }
            else{
                printf("It's a draw!\n");
                saveGame(gamemanager, tictactoe);
                break;
            }

        }
    }

}
