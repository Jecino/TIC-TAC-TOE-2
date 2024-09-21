#ifndef TICTACTOE_H
#define TICTACTOE_H

//Draw the game
void printTable(int tictactoe[][9]){

    //Will run the lines
    for(int i = 0; i < 9; i += 3){

        //Will run inside the rows, 3 by 3
        for(int j = 0; j <= 6; j+= 3){

            //Printing the first 3 numbers of each row, + 3 each loop
            for(int k = 0; k < 3; k++){
                printf("%d ", tictactoe[i][k+j]);
            }

            printf(" ");

            for(int k = 0; k < 3; k++){
                printf("%d ", tictactoe[i+1][k+j]);
            }

            printf(" ");

            for(int k = 0; k < 3; k++){
                printf("%d ", tictactoe[i+2][k+j]);
            }

            printf("\n");

        }

        printf("\n");

    }
}

//Checks if the small tictactoe already winned or its a draw
int checkComplete(int id, int tictactoe[][9]){
int zeros = 0, ones = 0, twos = 0;
    for(int i = 0; i < 9; i++){
        if (tictactoe[id][i] == 0){
            zeros ++;
        }
    }

    for(int i = 0; i < 9; i++){
        if (tictactoe[id][i] == 1){
            ones ++;
        }
    }

    for(int i = 0; i < 9; i++){
        if (tictactoe[id][i] == 2){
            twos++;
        }
    }

    if(zeros == 9 || ones == 9 || twos == 0){
        return 1;
    }

    return 0;
}

//For complete with some value when someone win a small tictactoe
void makeComplete(int id, int tictactoe[][9], int value){
    for(int s = 0; s < 9; s++){
        tictactoe[id][s] = value;
    }
}

//Check if the tictactoe is captured
void checkWinner(int tictactoe[][9], int id){
    int zerosRow = 0, zerosCollum = 0, onesCollum = 0, onesRow = 0, zerosDiag = 0, onesDiag = 0;

    //Will run the rows and collums checking if are captured
    for (int i = 0; i < 3; i++){
        if(tictactoe[id][i] == 0 && tictactoe[id][i+1] == 0 && tictactoe[id][i+2] == 0){
            zerosRow += 3;
        }
        else if(tictactoe[id][i] == 1 && tictactoe[id][i+1] == 1 && tictactoe[id][i+2] == 1){
            onesRow += 3;
        }

        //Check the collums

        if(tictactoe[id][i] == 0 && tictactoe[id][i+3] == 0 && tictactoe[id][i+6] == 0){
            zerosCollum += 3;
        }
        else if(tictactoe[id][i] == 1 && tictactoe[id][i+3] == 1 && tictactoe[id][i+6] == 1){
            onesCollum += 3;
        }

        //Checks the diagonals

        if(tictactoe[id][0] == 0 && tictactoe[id][4] == 0 && tictactoe[id][8] == 0){
            zerosDiag += 3;
        }
        else if(tictactoe[id][0] == 1 && tictactoe[id][4] == 1 && tictactoe[id][8] == 1){
            onesDiag += 3;
        }

        if(tictactoe[id][2] == 0 && tictactoe[id][4] == 0 && tictactoe[id][6] == 0){
            zerosDiag += 3;
        }
        else if(tictactoe[id][2] == 1 && tictactoe[id][4] == 1 && tictactoe[id][6] == 1){
            onesDiag += 3;
        }

        //If the row or collum is complete, will call the makecomplete function
        if(zerosRow == 3 || zerosCollum == 3 || zerosDiag == 3){
            makeComplete(id, tictactoe, 0);
            break;
        }
        else if(onesRow == 3 || onesCollum == 3 || onesDiag == 3){
            makeComplete(id, tictactoe, 1);
            break;
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
