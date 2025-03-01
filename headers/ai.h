#ifndef AI_H
#define AI_H

#include "functions.h"

int evaluateSmallBoard(char board[9], char player) {

    //Count the number of potential winning lines

    int score = 0;

    int lines[][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    for (int i = 0; i < 8; i++) {

        if (board[lines[i][0]] != player && board[lines[i][1]] != player && board[lines[i][2]] != player) {

            int count = (board[lines[i][0]] == '-') + (board[lines[i][1]] == '-') + (board[lines[i][2]] == '-');

            if (count == 3){
                score += 3;
            }

            else if (count == 2){
                score += 2;
            }

            else if (count == 1){
                score += 1; // Potential win
            }
        }

    }

    return score;

}

int evaluateBigBoard(char winned[9], char player) {

    // Count the number of potential winning lines

    int score = 0;

    int lines[][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    for (int i = 0; i < 8; i++) {

        if (winned[lines[i][0]] != player && winned[lines[i][1]] != player && winned[lines[i][2]] != player) {

            int count = (winned[lines[i][0]] == '-') + (winned[lines[i][1]] == '-') + (winned[lines[i][2]] == '-');

            if (count == 3){
                score += 3;
            }

            else if (count == 2){
                score += 2;
            }

            else if (count == 1){
                score += 1; // Potential win
            }
        }

    }

    return score;
}

int ValuatePlay(char PC, char tictactoe[][9], char winned[9], int lastplayed){
    int score = 0;
    char player = (PC == 'O') ? 'X' : 'O';

    //Evaluate small boards

    for (int i = 0; i < 9; i++) {

        if (winned[i] == PC) score += 100;

        else if (winned[i] == player) score -= 100;

        else {

            //Evaluate potential wins on small boards

            score += evaluateSmallBoard(tictactoe[i], PC) * 10;

            score -= evaluateSmallBoard(tictactoe[i], player) * 10;

        }

    }

    //Evaluate big board

    score += evaluateBigBoard(winned, PC) * 1000;

    score -= evaluateBigBoard(winned, player) * 1000;


    //Evaluate strategic positions

    int strategicPositions[5] = {0, 2, 4, 6, 8}; // Center and corners

    for (int i = 0; i < 5; i++) {

        if (winned[strategicPositions[i]] == PC) {
            score += 5;
        }
        else if (winned[strategicPositions[i]] == player) {
            score -= 5;
        }
    }

    //Try not play in a already winned board

    if(checkComplete(lastplayed, tictactoe) != 0){
        score -= 300;
    }

    return score;
}

int minmax(char tictactoe[][9], char winned[9], int lastplayed, int bigtictactoe, char PC, int ismax, int deep, int alpha, int beta){
    int best = 0, score = 0, currentScore = 0;
    char player = (PC == 'O') ? 'X' : 'O';

    score = ValuatePlay(PC, tictactoe, winned, lastplayed);

    if(score >= 200){
        return score + deep;
    }

    else if(score <= -200){
        return score - deep;
    }

    if(checkBigWinner(winned) != '-' || deep == 0){
        return score - deep;
    }

    if(ismax == 1){
        best =  -1000;
        for(int i = 0; i < 9; i++){

             if(tictactoe[lastplayed][i] == '-'){
                tictactoe[lastplayed][i] = PC;
                char old_winned = winned[i];
                winned[i] = checkWinner(tictactoe, i);

                currentScore = minmax(tictactoe, winned, i, 0, PC, 0, deep - 1, alpha, beta);
                best = best > currentScore ? best : currentScore;

                tictactoe[lastplayed][i] = '-';
                winned[i] = old_winned;
                alpha = alpha > best ? alpha : best;

                if(alpha >= beta) {
                    break;
                }

            }

        }

        return best;
    }


    else{
        best = 1000;
        for(int i = 0; i < 9; i++){

            if(tictactoe[lastplayed][i] == '-'){
                tictactoe[lastplayed][i] = player;
                char old_winned = winned[i];
                winned[i] = checkWinner(tictactoe, i);

                currentScore = minmax(tictactoe, winned, i, 0, PC, 1, deep - 1, alpha, beta);
                best = best < currentScore ? best : currentScore;
                tictactoe[lastplayed][i] = '-';
                winned[i] = old_winned;
                beta = beta < best ? beta : best;

                if(beta <= alpha) {
                    break;
                }
            }

        }
    return best;
    }
}

int bestplay(char tictactoe[][9], int lastplayed, char winned[9], char pc, int bigtictactoe){
    int bestvalue = -2147483648, playvalue = 0;
    int bestplace = -1;

    for(int j = 0; j < 9; j++){

        if(tictactoe[lastplayed][j] == '-' && bigtictactoe == 0){

            tictactoe[lastplayed][j] = pc;
            playvalue = minmax(tictactoe, winned, lastplayed, bigtictactoe, pc, 1, 5, -1000, 1000);
            tictactoe[lastplayed][j] = '-';

            if(playvalue > bestvalue){
                bestplace = j;
                bestvalue = playvalue;
            }
        }

        else if (bigtictactoe == 1){

            if(winned[j] != '-'){
                    continue;
                }

            for(int i = 0; i < 9; i++){


                tictactoe[j][i] = pc;
                playvalue = minmax(tictactoe, winned, i, 0, pc, 0, 5, -1000, 1000);
                tictactoe[j][i] = '-';

                if(playvalue > bestvalue){
                    bestplace = j;
                    bestvalue = playvalue;
                }
            }

        }
    }
    return bestplace + 1;
}

#endif