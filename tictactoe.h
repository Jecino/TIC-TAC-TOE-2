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
    int blocked = 0;

    for(int i = 0; i < 9; i++){
        if (checkComplete(i, tictactoe) == 1){
            blocked += 1;
        }
    }

    if(blocked == 9){
        return 0;
    }

    return 1;
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

//Check if the tictactoe is captured
char checkWinner(char tictactoe[][9], int id, int usingMinMax){
    int zerosRow = 0, zerosCollum = 0, onesRow = 0, onesCollum = 0, zerosDiag = 0, onesDiag = 0;

    //Will run the rows and collums checking if are captured
    for (int i = 0; i < 3; i++){
        if(tictactoe[id][i*3] == 'O' && tictactoe[id][i*3+1] == 'O' && tictactoe[id][i*3+2] == 'O'){
            zerosRow += 3;
        }
        else if(tictactoe[id][i*3] == 'X' && tictactoe[id][i*3+1] == 'X' && tictactoe[id][i*3+2] == 'X'){
            onesRow += 3;
        }

        //Check the collums

        if(tictactoe[id][i] == 'O' && tictactoe[id][i+3] == 'O' && tictactoe[id][i+6] == 'O'){
            zerosCollum += 3;
        }
        else if(tictactoe[id][i] == 'X' && tictactoe[id][i+3] == 'X' && tictactoe[id][i+6] == 'X'){
            onesCollum += 3;
        }

        if((zerosRow == 3 || zerosCollum == 3) && usingMinMax == 0){
            makeComplete(id, tictactoe, 'O');
            return 'O';
        }
        else if((onesRow == 3 || onesCollum == 3) && usingMinMax == 0){
            makeComplete(id, tictactoe, 'X');
            return 'X';
        }
    }

    //Checks the diagonals

    if(tictactoe[id][0] == 'O' && tictactoe[id][4] == 'O' && tictactoe[id][8] == 'O'){
        zerosDiag += 3;
    }
    else if(tictactoe[id][0] == 'X' && tictactoe[id][4] == 'X' && tictactoe[id][8] == 'X'){
        onesDiag += 3;
    }

    if(tictactoe[id][2] == 'O' && tictactoe[id][4] == 'O' && tictactoe[id][6] == 'O'){
        zerosDiag += 3;
    }
    else if(tictactoe[id][2] == 'X' && tictactoe[id][4] == 'X' && tictactoe[id][6] == 'X'){
        onesDiag += 3;
    }

    //If the row or collum is complete, will call the makecomplete function
    if(zerosDiag == 3 && usingMinMax == 0){
        makeComplete(id, tictactoe, 'O');
        return 'O';
    }
    else if(onesDiag == 3 && usingMinMax == 0){
        makeComplete(id, tictactoe, 'X');
        return 'X';
    }

    return '-';

}

//Check big winning
char checkBigWinner(char tictactoe[]){
    int zerosRow = 0, zerosCollum = 0, onesRow = 0, onesCollum = 0, zerosDiag = 0, onesDiag = 0;

    //Will run the rows and collums checking if are captured
    for (int i = 0; i < 3; i++){

        //Check the rows

        zerosRow = (tictactoe[i*3] == 'O') + (tictactoe[i*3+1] == 'O') + (tictactoe[i*3+2] == 'O');
        onesRow = (tictactoe[i*3] == 'X') + (tictactoe[i*3+1] == 'X') + (tictactoe[i*3+2] == 'X');

        //Check the collums

        zerosCollum = (tictactoe[i] == 'O') + (tictactoe[i+3] == 'O') + (tictactoe[i+6] == 'O');
        onesCollum = (tictactoe[i] == 'X') + (tictactoe[i+3] == 'X') + (tictactoe[i+6] == 'X');

        //Checks the diagonals

        zerosDiag = (tictactoe[0] == 'O') + (tictactoe[4] == 'O') + (tictactoe[8] == 'O');
        onesDiag = (tictactoe[0] == 'X') + (tictactoe[4] == 'X') + (tictactoe[8] == 'X');

        if(zerosRow == 3 || zerosCollum == 3 || zerosDiag == 3){
            return 'O';
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            return 'X';
        }

        zerosDiag = 0;
        onesDiag = 0;

        zerosDiag = (tictactoe[2] == 'O') + (tictactoe[4] == 'O') + (tictactoe[6] == 'O');
        onesDiag = (tictactoe[2] == 'X') + (tictactoe[4] == 'X') + (tictactoe[6] == 'X');

        //If the row or collum is complete
        if(zerosRow == 3 || zerosCollum == 3 || zerosDiag == 3){
            return 'O';
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            return 'X';
        }
    }
    return '-';
}

int minmax(char tictactoe[][9], char winned[9], int lastplayed, int bigtictactoe, char PC, int ismax, int deep){
    int best = 0, score = 0;
    char player = (PC == 'O') ? 'X' : 'O';
    char tempWinner;

    tempWinner = checkWinner(tictactoe, lastplayed, 0);
    if(tempWinner == PC){
        score += 10;
    }
    else if (tempWinner == player){
        score -= 10;
    }
    else if (winned[lastplayed] != '-'){
        score -= 30;
    }
    else if(winned[lastplayed] == '-'){
        score += 30;
    }

    tempWinner = checkBigWinner(winned);
    if(tempWinner == PC){
        score += 100;
    }
    else if (tempWinner == player){
        score -= 100;
    }

    if(score >= 100){
        return score - deep;
    }

    if(score <= -100){
        return score + deep;
    }

    if(checkMoves(tictactoe) == 0 || deep == 0){
        return score - deep;
    }

    if(ismax == 1){
        best =  -1000;
        for(int i = 0; i < 9; i++){

            if(bigtictactoe == 1 && winned[i] != '-'){
                continue;
            }

             if(tictactoe[lastplayed][i] == '-'){
                tictactoe[lastplayed][i] = PC;
                best = best > minmax(tictactoe, winned, i, 0, PC, 0, deep - 1) ? best : minmax(tictactoe, winned, i, 0, PC, 0, deep - 1);
                tictactoe[lastplayed][i] = '-';
            }
        }
        return best;
    }


    else{
        best = 1000;
        for(int i = 0; i < 9; i++){

            if(bigtictactoe == 1 && winned[i] != '-'){
                continue;
            }

            if(tictactoe[lastplayed][i] == '-'){
                tictactoe[lastplayed][i] = player;
                best = best < minmax(tictactoe, winned, i, 0, PC, 1, deep - 1) ? best : minmax(tictactoe, winned, i, 0, PC, 1, deep - 1);
                tictactoe[lastplayed][i] = '-';
            }
        }
    return best;
    }
}

int bestplay(char tictactoe[][9], int lastplayed, char winned[9], char pc, int bigtictactoe){
    int bestvalue = -2147483648, playvalue = 0;
    int bestplace = -1;

    for(int j = 0; j < 9; j++){

        if(bigtictactoe == 1 && winned[j] != '-'){
                continue;
        }

        if(tictactoe[lastplayed][j] == '-'){

            tictactoe[lastplayed][j] = pc;
            playvalue = minmax(tictactoe, winned, lastplayed, bigtictactoe, pc, 0, 5);
            tictactoe[lastplayed][j] = '-';

            if(playvalue > bestvalue){
                bestplace = j;
                bestvalue = playvalue;
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
                    for(int i = 0; i < 9; i++){
                        for(int j = 0; j < 9; j++){
                            copiedtable[i][j] = tictactoe[i][j];
                        }
                    }
                    gamemanager -> choosedPos = bestplay(copiedtable, gamemanager->lastPos2 - 1,gamemanager->winned, (gamemanager->PC == 1) ? 'X' : 'O', 1);
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
                    for(int i = 0; i < 9; i++){
                        for(int j = 0; j < 9; j++){
                            copiedtable[i][j] = tictactoe[i][j];
                        }
                    }
                gamemanager -> choosedPos2 = bestplay(copiedtable, gamemanager->lastPos2 - 1,gamemanager->winned, (gamemanager->PC == 1) ? 'X' : 'O', 0);
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
        checkWinner(tictactoe, gamemanager -> choosedPos - 1, 0);
    }
    else{
        checkWinner(tictactoe, gamemanager -> lastPos2 - 1, 0);
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
