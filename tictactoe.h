#ifndef TICTACTOE_H
#define TICTACTOE_H

//Gamemanager creation
typedef struct{
    int lastPos, choosedPos, lastPos2, choosedPos2, lastPlayer, nextPlayer;
    char winned[9];

} Tgamemanager;

//Table declaration
char tictactoe[9][9];

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
                printf("%c ", tictactoe[i][k+j]);
            }

            printf(" ");

            for(int k = 0; k < 3; k++){
                printf("%c ", tictactoe[i+1][k+j]);
            }

            printf(" ");

            for(int k = 0; k < 3; k++){
                printf("%c ", tictactoe[i+2][k+j]);
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
char checkWinner(char tictactoe[][9], int id){
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
        if(zerosRow == 3 || zerosCollum == 3 || zerosDiag == 3){
            makeComplete(id, tictactoe, 'O');
            return 'O';
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            makeComplete(id, tictactoe, 'X');
            return 'X';
        }
        else{
            //Clean the values for the next iteration
            zerosRow = 0;
            onesRow = 0;
            zerosCollum = 0;
            onesCollum = 0;
            zerosDiag = 0;
            onesDiag = 0;
        }
    }

    return '-';

}

//Check big winning
char checkBigWinner(char tictactoe[]){
    int zerosRow = 0, zerosCollum = 0, onesRow = 0, onesCollum = 0, zerosDiag = 0, onesDiag = 0;

    //Will run the rows and collums checking if are captured
    for (int i = 0; i < 3; i++){
        if(tictactoe[i*3] == 'O' && tictactoe[i*3+1] == 'O' && tictactoe[i*3+2] == 'O'){
            zerosRow += 3;
        }
        else if(tictactoe[i*3] == 'X' && tictactoe[i*3+1] == 'X' && tictactoe[i*3+2] == 'X'){
            onesRow += 3;
        }

        //Check the collums

        if(tictactoe[i] == 'O' && tictactoe[i+3] == 'O' && tictactoe[i+6] == 'O'){
            zerosCollum += 3;
        }
        else if(tictactoe[i] == 'X' && tictactoe[i+3] == 'X' && tictactoe[i+6] == 'X'){
            onesCollum += 3;
        }

        //Checks the diagonals

        if(tictactoe[0] == 'O' && tictactoe[4] == 'O' && tictactoe[8] == 'O'){
            zerosDiag += 3;
        }
        else if(tictactoe[0] == 'X' && tictactoe[4] == 'X' && tictactoe[8] == 'X'){
            onesDiag += 3;
        }

        if(tictactoe[2] == 'O' && tictactoe[4] == 'O' && tictactoe[6] == 'O'){
            zerosDiag += 3;
        }
        else if(tictactoe[2] == 'X' && tictactoe[4] == 'X' && tictactoe[6] == 'X'){
            onesDiag += 3;
        }

        //If the row or collum is complete, will call the makecomplete function
        if(zerosRow == 3 || zerosCollum == 3 || zerosDiag == 3){
            return 'O';
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            return 'X';
        }
        else{
            //Clean the values for the next iteration
            zerosRow = 0;
            onesRow = 0;
            zerosCollum = 0;
            onesCollum = 0;
            zerosDiag = 0;
            onesDiag = 0;
        }
    }
    return '-';
}

void jogada(Tgamemanager *gamemanager, int actualPlayer, int ChooseBigTicTacToe){
    int choosedBigTicTacToe = 0;
    //Say who begins
    //If is the first play, makes the random number the next player
    if(gamemanager -> lastPos == -1){
        clear();
        printTable(tictactoe);
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
            printf("\nChoose where you will play (in the big tic tac toe): ");
            scanf(" %d", &gamemanager -> choosedPos);

            if(checkComplete(gamemanager -> choosedPos - 1, tictactoe) != 0){
                printf("That tic tac toe is not avaliable, choose another\n");
                continue;
            }

            if(gamemanager -> choosedPos < 1 || gamemanager -> choosedPos > 9){
                printf("That positon is not valid, choose another\n");
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
        printf("\nChoose where you will play: ");
        scanf(" %d", &gamemanager -> choosedPos2);

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

    clear();

    if(gamemanager -> lastPos == -1 || choosedBigTicTacToe == 1){
        checkWinner(tictactoe, gamemanager -> choosedPos - 1);
    }
    else{
        checkWinner(tictactoe, gamemanager -> lastPos2 - 1);
    }

    printTable(tictactoe);

    //Variable's update
    gamemanager -> lastPlayer = gamemanager -> nextPlayer;
    gamemanager -> nextPlayer = (gamemanager -> lastPlayer == 0) ? 1 : 0;

    gamemanager -> lastPos = gamemanager -> choosedPos;
    gamemanager -> lastPos2 = gamemanager -> choosedPos2;
}

#endif
