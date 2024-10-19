#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int main()
{
    //Variables
    char rsp = '0';
    char exitingrsp;
    FILE* save;
    srand(time(0));

    initializeTable(tictactoe, '-');

    //Random int for choose who begins
    int r = randomNumber(2);

    int pc = randomNumber(2);

    Tgamemanager gamemanager;

    for(int i = 0; i < 9; i++){
        gamemanager.winned[i] = '-';
    }

    do{
        printf("Welcome to the Tic Tac Toe 2!\n\n");
        printf("1. New Game\n2. Continue\n3. How to play\n4. Exit\n");
        scanf(" %c", &rsp);

        switch(rsp){
            case '1':
                printf("\nWhat type of game?\n1. Player vs Computer\n2. Player vs Player\n");
                scanf(" %c", &rsp);

                switch(rsp){
                    case '1':
                        gamemanager.PC = (r == pc) ? r : pc;
                        printf("Creating the table...\n");
                        gamemanager.lastPos = -1;
                        gamemanager.lastPos2 = -1;
                        sleep(1);
                        rsp = '0';
                        break;

                    case '2':
                        gamemanager.PC = -1;
                        printf("Creating the table...\n");
                        gamemanager.lastPos = -1;
                        sleep(1);
                        rsp = '0';
                        break;

                    default:
                        printf("Could not recognize your option, try again\n");
                        sleep(1);
                        break;
                }

                break;

            case '2':
                save = fopen("save.tic", "r");
                printf("\nLoading the save\n");

                loadGame(save, &gamemanager, &tictactoe);

                sleep(1);

                rsp = '0';

                break;

            case '3':
                tutorial();
                break;

            case '4':
                printf("Bye :D\n");
                return 0;

            default:
                printf("Could not recognize your option, try again\n");
                sleep(1);
                break;
        }

        clear();
    } while(rsp != '0');

    //gameloop
    while(1){
        clear();
        printTable(tictactoe);

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

        if (checkMoves(tictactoe) == 0){
            clear();
            printTable(tictactoe);
            printf("It's a draw!\n");
            break;
        }

        if(checkBigWinner(gamemanager.winned)!= '-'){
            if(gamemanager.lastPlayer == 0){
                clear();
                printTable(tictactoe);
                printf("The \"O\" is the winner!\n");
                break;
            }
            else if (gamemanager.lastPlayer == 1){
                clear();
                printTable(tictactoe);
                printf("The \"X\" is the winner!\n");
                break;
            }
        }

        if(gamemanager.exited == 1){

            do{
                clear();
                printf("\nYou want to save before exit? (y/n)\n");
                scanf(" %c", &exitingrsp);

                if(exitingrsp == 'y'){
                    saveGame(gamemanager, tictactoe);
                    printf("\nGame saved\n");
                }
            } while(exitingrsp != 'y' && exitingrsp != 'n');

            printf("\nBye :D!\n");
            break;
        }
    }

}
