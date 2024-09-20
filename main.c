#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int main()
{
    //Variables
    int tictactoe[9][9];

    //Fill the array for better view
    for(int k = 0; k < 9; k++){
        for(int s = 0; s < 9; s++){
            tictactoe[k][s] = 2;
        }
    }

    //Random int for choose who begins
    srand(time(NULL));
    int r = rand() % 2;

    //Gamemanager creation
    typedef struct{
        int lastPos, choosedPos, lastPos2, choosedPos2, lastPlayer, nextPlayer;

    } Tgamemanager;


    Tgamemanager gamemanager;
    gamemanager.lastPos = -1;

    //gameloop
    while(1){
        if (gamemanager.lastPos == -1){

            //print the game
            printTable(tictactoe);

            //Say who begins
            if(r == 0){
                printf("The \"X\" begins!\n");
            }
            else if(r == 1){
                printf("The \"O\" begins!\n");
            }

            //Asking where to play, and storing it in the gamemanager
            printf("\nChoose which tic tac toe you will play: ");
            scanf(" %d", &gamemanager.choosedPos);

            system("clear");
            printTable(tictactoe);

            printf("\nChoose where you will play: ");
            scanf(" %d", &gamemanager.choosedPos2);

            gamemanager.lastPos = gamemanager.choosedPos;
            gamemanager.lastPos2 = gamemanager.choosedPos2;
            gamemanager.lastPlayer = r;


            //Changes the table depending in who are the player in the moment
            tictactoe[gamemanager.choosedPos][gamemanager.choosedPos2] = (r == 0) ? 0 : 1;

            if (r == 0){gamemanager.nextPlayer = 1;}

            else{gamemanager.nextPlayer = 0;}

            system("clear");
            printTable(tictactoe);
        }

        //Checks if the last choosed small tictactoe is completed, if not runs
        if (checkComplete(gamemanager.lastPos2, tictactoe) == 0){

            //Say who begins
            if(gamemanager.nextPlayer == 0){
                printf("The \"X\" plays!\n");
            }
            else if(gamemanager.nextPlayer == 1){
                printf("The \"O\" plays!\n");
            }

            printf("\nChoose where you will play: ");
            scanf(" %d", &gamemanager.choosedPos2);

            //Changes the table depending in who are the player in the moment
            tictactoe[gamemanager.lastPos2][gamemanager.choosedPos2] = (r == 0) ? 0 : 1;

            system("clear");
            printTable(tictactoe);

            //Variable's update
            gamemanager.lastPos = gamemanager.choosedPos;
            gamemanager.lastPos2 = gamemanager.choosedPos2;
            gamemanager.lastPlayer = gamemanager.nextPlayer;

            if (gamemanager.lastPlayer == 0){gamemanager.nextPlayer = 1;}

            else{gamemanager.nextPlayer = 0;}
        }

        //Gives the player oportunity to choose where will play in the big tictactoe
        else{

        }
    }
}
