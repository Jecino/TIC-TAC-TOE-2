#ifndef TICTACTOE_H
#define TICTACTOE_H
#include "functions.h"
#include "ai.h"

void jogada(Tgamemanager *gamemanager, int actualPlayer, int ChooseBigTicTacToe){
    int choosedBigTicTacToe = 0;
    //Say who begins
    //If is the first play, makes the random number the next player
    if(gamemanager -> lastPos == -1){
        gamemanager -> nextPlayer = actualPlayer;

        if(gamemanager -> nextPlayer == 1){
            printf("The \"X\" begins!\n");
        }
        else if(gamemanager -> nextPlayer == 0){
            printf("The \"O\" begins!\n");
        }
    }

    else{
        if(gamemanager -> nextPlayer == 1){
            printf("The \"X\" plays!\n");
        }
        else if(gamemanager -> nextPlayer == 0){
            printf("The \"O\" plays!\n");
        }
    }

    //Asks where play in the big tac toe if needed
    if(ChooseBigTicTacToe == 1){
        do{
            int tempPos = gamemanager -> choosedPos;
            if(gamemanager ->nextPlayer != gamemanager->PC){
                printf("\nChoose where you will play (in the big tic tac toe): ");


                while(scanf(" %d", &gamemanager -> choosedPos) != 1){
                    printf("\nEnter a valid number");
                    getchar();
                }
            }

            else{
                if(gamemanager -> lastPos == -1){
                    gamemanager-> choosedPos = randomNumber(8) + 1;
                }
                else{
                    char copiedtable[9][9];
                    char copiedWinned[9];
                    for(int i = 0; i < 9; i++){
                            copiedWinned[i] = gamemanager -> winned[i];
                        for(int j = 0; j < 9; j++){
                            copiedtable[i][j] = tictactoe[i][j];
                        }
                    }
                    gamemanager -> choosedPos = bestplay(copiedtable, gamemanager->lastPos2 - 1, copiedWinned, (gamemanager->PC == 1) ? 'X' : 'O', 1);
                    choosedBigTicTacToe = 1;
                }
            }


            if(gamemanager -> choosedPos == 0){

                gamemanager -> choosedPos = tempPos;
                gamemanager -> exited = 1;
                return;
            }

            if(checkComplete(gamemanager -> choosedPos - 1, tictactoe) != 0){
                printf("That tic tac toe is not avaliable, choose another\n");
                continue;
            }

            if(gamemanager -> choosedPos < 1 || gamemanager -> choosedPos > 9){
                printf("That position is not valid, choose another\n");
            }

            else{
                choosedBigTicTacToe = 1;
                break;
            }

        } while(1);
    }

    if(gamemanager -> lastPos == -1 || choosedBigTicTacToe == 1){
        printf("Current selected tictactoe:  %d\n", gamemanager -> choosedPos);
    }
    else{
        printf("Current selected tictactoe:  %d\n", gamemanager -> lastPos2);
    }

    //Asks where to play, and ckeck if is already played
    do{
        int tempPos2 = gamemanager -> choosedPos2;
        if(gamemanager ->nextPlayer != gamemanager->PC){
                printf("\nChoose where you will play: ");


                while(scanf(" %d", &gamemanager -> choosedPos2) != 1){
                    printf("\nEnter a valid number");
                    getchar();
                }
            }

        else{
            if(gamemanager -> lastPos2 == -1){
                gamemanager-> choosedPos2 = randomNumber(8) + 1;
            }
            else{
                char copiedtable[9][9];
                char copiedWinned[9];
                    for(int i = 0; i < 9; i++){
                            copiedWinned[i] = gamemanager->winned[i];
                        for(int j = 0; j < 9; j++){
                            copiedtable[i][j] = tictactoe[i][j];
                        }
                    }

                    if(choosedBigTicTacToe == 1){
                        gamemanager -> choosedPos2 = bestplay(copiedtable, gamemanager->choosedPos - 1, copiedWinned, (gamemanager->PC == 1) ? 'X' : 'O', 0);
                    }
                    else{
                        gamemanager -> choosedPos2 = bestplay(copiedtable, gamemanager->lastPos2 - 1, copiedWinned, (gamemanager->PC == 1) ? 'X' : 'O', 0);
                    }
            }

        }

        if(gamemanager -> choosedPos2 == 0){
            gamemanager -> choosedPos2 = tempPos2;
            gamemanager -> exited = 1;
            return;
        }

        if(gamemanager -> lastPos == -1 || choosedBigTicTacToe == 1){
            if(tictactoe[gamemanager -> choosedPos - 1][gamemanager -> choosedPos2 - 1] != '-'){
                printf("That position have been already played, choose another\n");
                continue;
            }
        }

        else{
            if(tictactoe[gamemanager -> lastPos2 - 1][gamemanager -> choosedPos2 - 1] != '-'){
                printf("That position have been already played, choose another\n");
                continue;
            }
        }

        if(gamemanager -> choosedPos2 < 1 || gamemanager -> choosedPos2 > 9){
            printf("That positon is not valid, choose another\n");
        }

        else{
            break;
        }

    } while(1);

    //Changes the table depending in who are the player in the moment
    if(gamemanager -> lastPos == -1 || choosedBigTicTacToe == 1){
        tictactoe[gamemanager -> choosedPos - 1][gamemanager -> choosedPos2 - 1] = (gamemanager -> nextPlayer == 0) ? 'O' : 'X';
    }
    else{
        tictactoe[gamemanager -> lastPos2 - 1][gamemanager -> choosedPos2 - 1] = (gamemanager -> nextPlayer == 0) ? 'O' : 'X';
    }

    if(gamemanager -> lastPos == -1 || choosedBigTicTacToe == 1){
        checkWinner(tictactoe, gamemanager -> choosedPos - 1);
    }
    else{
        checkWinner(tictactoe, gamemanager -> lastPos2 - 1);
    }

    //Variable's update
    gamemanager -> lastPlayer = gamemanager -> nextPlayer;
    gamemanager -> nextPlayer = (gamemanager -> lastPlayer == 0) ? 1 : 0;

    gamemanager -> lastPos = gamemanager -> choosedPos;
    gamemanager -> lastPos2 = gamemanager -> choosedPos2;
}
#endif