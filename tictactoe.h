#ifndef TICTACTOE_H
#define TICTACTOE_H

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
        if (tictactoe[id][i] == 'H'){
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
int checkWinner(char tictactoe[][9], int id){
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
            return 0;
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            makeComplete(id, tictactoe, 'X');
            return 1;
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

    return -1;

}

//Check big winning
int checkBigWinner(char tictactoe[]){
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
            return 0;
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            return 1;
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
    return -1;
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

#endif
