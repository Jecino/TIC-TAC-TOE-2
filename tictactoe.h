#ifndef TICTACTOE_H
#define TICTACTOE_H

//Gamemanager creation
typedef struct{
    int lastPos, choosedPos, lastPos2, choosedPos2, lastPlayer, nextPlayer, exited;
    char winned[9];
    char PC;

} Tgamemanager;

//Table declaration
char tictactoe[9][9];

void initializeTable(char tictactoe[][9], char value){
    //Fill the table for better view
    for(int k = 0; k < 9; k++){
        for(int s = 0; s < 9; s++){
            tictactoe[k][s] = value;
        }
    }
}

int randomNumber(int maximum){
    return rand() % maximum;
}

int checkMoves(char tictactoe[][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tictactoe[i][j] == '-') {
                return 1;
            }
        }
    }
    return 0;
}

//clear the console in different OS
void clear(){
    #ifdef _WIN32
        system("cls");

    #elif __linux__
        system("clear");

    #else
        printf("Can't detect the OS");

    #endif
        return;
}

//Draw the game
void printTable(char tictactoe[][9]){

    //Will run the lines
    for(int i = 0; i < 9; i += 3){

        //Will run inside the rows, 3 by 3
        for(int j = 0; j <= 6; j+= 3){

            //Printing the first 3 numbers of each row, + 3 each loop
            for(int k = 0; k < 3; k++){
                printf(" %c", tictactoe[i][k+j]);
            }

            printf(" ");

            for(int k = 0; k < 3; k++){
                printf(" %c", tictactoe[i+1][k+j]);
            }

            printf(" ");

            for(int k = 0; k < 3; k++){
                printf(" %c", tictactoe[i+2][k+j]);
            }

            printf("\n");

        }

        printf("\n");

    }
}

//Checks if the small tictactoe already winned or its a draw
int checkComplete(int id, char tictactoe[][9]){
    int zeros = 0, ones = 0, twos = 0;

    for(int i = 0; i < 9; i++){
        if (tictactoe[id][i] == 'O'){
            zeros ++;
        }
    }

    for(int i = 0; i < 9; i++){
        if (tictactoe[id][i] == 'X'){
            ones ++;
        }
    }

    for(int i = 0; i < 9; i++){
        if (tictactoe[id][i] == '-'){
            twos++;
        }
    }

    if(zeros == 9 || ones == 9 || twos == 0){
        return 1;
    }

    return 0;
}

//For complete with some value when someone win a small tictactoe
void makeComplete(int id, char tictactoe[][9], char value){
    for(int s = 0; s < 9; s++){
        tictactoe[id][s] = value;
    }
}

//Check winning in the small board
char checkWinner(char board[][9], int id){

    //List of lines, collums and diagonals to check

    int lines[][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    for (int i = 0; i < 8; i++) {

        if (board[id][lines[i][0]] == 'X' && board[id][lines[i][1]] == 'X' && board[id][lines[i][2]] == 'X') {
            makeComplete(id, board, 'X');
            return 'X';
        }
        else if (board[id][lines[i][0]] == 'O' && board[id][lines[i][1]] == 'O' && board[id][lines[i][2]] == 'O'){
            makeComplete(id, board, 'O');
            return 'O';
        }

    }

    return '-';
}

//Check winning in big board
char checkBigWinner(char board[]){

    //List of lines, collums and diagonals to check

    int lines[][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

    for (int i = 0; i < 8; i++) {

        if (board[lines[i][0]] == 'X' && board[lines[i][1]] == 'X' && board[lines[i][2]] == 'X') {
            return 'X';
        }
        else if (board[lines[i][0]] == 'O' && board[lines[i][1]] == 'O' && board[lines[i][2]] == 'O'){
            return 'O';
        }

    }

    return '-';
}

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
    char tempWinner;
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

    if(score >= 300){
        return score + deep;
    }

    if(score <= -300){
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
            for(int i = 0; i < 9; i++){
                if(winned[j] != '-'){
                    continue;
                }

                tictactoe[j][i] = pc;
                playvalue = minmax(tictactoe, winned, i, bigtictactoe, pc, 0, 5, -1000, 1000);
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
                            copiedWinned[i] == gamemanager->winned[i];
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

void saveGame(Tgamemanager gamemanager, char tictactoe[][9]){
    FILE* save;
    save = fopen("save.tic", "w");

    if(save == NULL){
        printf("Can't save the game, try again\n");
        return;
    }

    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j++){
            fprintf(save, "%c", tictactoe[i][j]);
        }
        fprintf(save, "\n");
    }

    fprintf(save, "%d %d %d %d %d %d\n", gamemanager.choosedPos2, gamemanager.choosedPos, gamemanager.lastPlayer, gamemanager.lastPos2, gamemanager.lastPos, gamemanager.nextPlayer);

    for(int i = 0; i < 9; i++){
        fprintf(save, "%c", gamemanager.winned[i]);
    }

    fclose(save);
}

void loadGame(FILE* load, Tgamemanager *gamemanager, char tictactoe[][9]){

    if(load == NULL){
        printf("Can't load the game, try again\n");
        return;
    }

    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j++){
            fscanf(load, "%c", &tictactoe[i][j]);
        }
        fscanf(load, "\n");
    }

    fscanf(load, "%d %d %d %d %d %d\n", &gamemanager -> choosedPos2, &gamemanager -> choosedPos, &gamemanager -> lastPlayer, &gamemanager -> lastPos2, &gamemanager -> lastPos, &gamemanager -> nextPlayer);

    for(int i = 0; i < 9; i++){
        fscanf(load, "%c", &gamemanager -> winned[i]);
    }

    fclose(load);
}

void tutorial(){
    char rsp;
    do{
        clear();
        char line[150];

        FILE* tutorial;
        tutorial = fopen("tutorial.txt", "r");

        if(tutorial == NULL){
            printf("Can't open the tutorial file, try again");
            return;
        }

        while(fgets(line, 150, tutorial) != NULL){
            printf("%s", line);
        }


        fclose(tutorial);

        printf("\n\nWish going back to the menu? (y/n): ");
        scanf(" %c", &rsp);
    } while(rsp != 'y' && rsp!= 'n');
}

#endif
