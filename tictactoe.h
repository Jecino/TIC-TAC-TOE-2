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

#endif
