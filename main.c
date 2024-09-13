#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw.h"

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
        int lastPos, choosedPos, lastPos2, choosedPos2, lastPlayer;

    } Tgamemanager;


    Tgamemanager gamemanager;
    gamemanager.lastPos = -1;

    //gameloop
    while(1){
        if (gamemanager.lastPos == -1){
            printTable(tictactoe);

            if(r == 0){
                printf("The \"X\" begins!\n");
            }
            else if(r == 1){
                printf("The \"O\" begins!\n");
            }

            printf("\nChoose which tic tac toe you will play: ");
            scanf(" %d", &gamemanager.choosedPos);

            system("clear");
            printTable(tictactoe);

            printf("\nChoose where you will play: ");
            scanf(" %d", &gamemanager.choosedPos2);

            gamemanager.lastPos = gamemanager.choosedPos;
            gamemanager.lastPos2 = gamemanager.choosedPos2;
            gamemanager.lastPlayer = r;


            tictactoe[gamemanager.choosedPos][gamemanager.choosedPos2] = (r == 0) ? 0 : 1;

            system("clear");
            printTable(tictactoe);
        }
    }
}
