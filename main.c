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
        int winned[9];

    } Tgamemanager;


    Tgamemanager gamemanager;
    gamemanager.lastPos = -1;

    //gameloop
    while(1){

        //Enter here if is the fist play
        if (gamemanager.lastPos == -1){

            //print the game
            printTable(tictactoe);

            //Say who begins
            if(r == 1){
                printf("The \"X\" begins!\n");
            }
            else if(r == 0){
                printf("The \"O\" begins!\n");
            }

            //Asking where to play, and storing it in the gamemanager
            do{
                printf("\nChoose where you will play: ");
                scanf(" %d", &gamemanager.choosedPos);

                if(gamemanager.choosedPos < 1 || gamemanager.choosedPos > 9){
                    printf("That positon is not valid, choose another\n");
                }

                else{
                    break;
                }

            } while(1);

            clear();
            printTable(tictactoe);
            printf("Current selected tictactoe:  %d\n", gamemanager.choosedPos);


            do{
                printf("\nChoose where you will play: ");
                scanf(" %d", &gamemanager.choosedPos2);

                if(gamemanager.choosedPos2 < 1 || gamemanager.choosedPos2 > 9){
                    printf("That positon is not valid, choose another\n");
                }

                else{
                    break;
                }

            } while(1);

            gamemanager.lastPos = gamemanager.choosedPos;
            gamemanager.lastPos2 = gamemanager.choosedPos2;
            gamemanager.lastPlayer = r;


            //Changes the table depending in who are the player in the moment
            tictactoe[gamemanager.choosedPos - 1][gamemanager.choosedPos2 - 1] = (r == 0) ? 0 : 1;

            if (r == 0){gamemanager.nextPlayer = 1;}

            else{gamemanager.nextPlayer = 0;}

            clear();
            printTable(tictactoe);
        }

        //Checks if the last choosed small tictactoe is completed, if not: runs
        if (checkComplete(gamemanager.lastPos2 - 1, tictactoe) == 0){

            //Say who begins
            if(gamemanager.nextPlayer == 1){
                printf("The \"X\" plays!\n");
            }
            else if(gamemanager.nextPlayer == 0){
                printf("The \"O\" plays!\n");
            }

            printf("Current selected tictactoe:  %d\n", gamemanager.lastPos2);

            //Asks where to play, and if is already played
            do{
                printf("\nChoose where you will play: ");
                scanf(" %d", &gamemanager.choosedPos2);

                if(tictactoe[gamemanager.lastPos2 - 1][gamemanager.choosedPos2 - 1] != 2){
                    printf("That position have been already played, choose another\n");
                    continue;
                }

                if(gamemanager.choosedPos2 < 1 || gamemanager.choosedPos2 > 9){
                    printf("That positon is not valid, choose another\n");
                }

                else{
                    break;
                }

            } while(1);

            //Changes the table depending in who are the player in the moment
            tictactoe[gamemanager.lastPos2 - 1][gamemanager.choosedPos2 - 1] = (gamemanager.nextPlayer == 0) ? 0 : 1;

            clear();

            checkWinner(tictactoe, gamemanager.lastPos2 - 1);

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
            //Say who begins
            if(gamemanager.nextPlayer == 1){
                printf("The \"X\" plays!\n");
            }
            else if(gamemanager.nextPlayer == 0){
                printf("The \"O\" plays!\n");
            }

            printf("The last played position tic tac toe is not avaliable, you can choose another\n");

            do{
                printf("\nChoose where you will play: ");
                scanf(" %d", &gamemanager.choosedPos);

                if(checkComplete(gamemanager.choosedPos - 1, tictactoe) != 0){
                    printf("That tic tac toe is not avaliable, choose another\n");
                    continue;
                }

                if(gamemanager.choosedPos2 < 1 || gamemanager.choosedPos2 > 9){
                    printf("That positon is not valid, choose another\n");
                }

                else{
                    break;
                }

            } while(1);

            clear();
            printTable(tictactoe);

            printf("Current selected tictactoe:  %d\n", gamemanager.choosedPos);

            //Asks where to play, and if is already played
            do{
                printf("\nChoose where you will play: ");
                scanf(" %d", &gamemanager.choosedPos2);

                if(tictactoe[gamemanager.choosedPos - 1][gamemanager.choosedPos2 - 1] != 2){
                    printf("That position have been already played, choose another\n");
                }

                if(gamemanager.choosedPos2 < 1 || gamemanager.choosedPos2 > 9){
                    printf("That positon is not valid, choose another\n");
                }

                else{
                    break;
                }

            } while(1);

            //Changes the table depending in who are the player in the moment
            tictactoe[gamemanager.choosedPos - 1][gamemanager.choosedPos2 - 1] = (gamemanager.nextPlayer == 0) ? 0 : 1;

            clear();

            checkWinner(tictactoe, gamemanager.choosedPos - 1);

            printTable(tictactoe);

            //Variable's update
            gamemanager.lastPos = gamemanager.choosedPos;
            gamemanager.lastPos2 = gamemanager.choosedPos2;
            gamemanager.lastPlayer = gamemanager.nextPlayer;

            if (gamemanager.lastPlayer == 0){gamemanager.nextPlayer = 1;}

            else{gamemanager.nextPlayer = 0;}
        }

        //Check if the big tic tac toe is winned

        for(int i = 0; i < 9; i++){
            gamemanager.winned[i] = checkWinner(tictactoe, i);
        }

        if(checkBigWinner(gamemanager.winned)!= -1){
            if(gamemanager.lastPlayer == 0){
                printf("The \"O\" is the winner!\n");
                break;
            }
            else{
                printf("The \"X\" is the winner!\n");
                break;
            }

        }
    }

}
