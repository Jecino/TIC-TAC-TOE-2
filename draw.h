#ifndef DRAW_H
#define DRAW_H

void printTable(int tictactoe[][9]){

    for(int i = 0; i < 9; i+= 3){

        for(int k = 0; k < 9; k += 3){


        }
        for(int j = 0; j < 3; j++){
            printf(" %d ", tictactoe[i][j]);

            if(((j+1) % 3) == 0){
                printf(" ");
            }
        }

        for(int j = 0; j < 3; j++){
            printf(" %d ", tictactoe[i + 1][j]);

            if(((j+1) % 3) == 0){
                printf(" ");
            }
        }

        for(int j = 0; j < 3; j++){
            printf(" %d ", tictactoe[i + 2][j]);

            if(((j+1) % 3) == 0){
                printf(" ");
            }
        }



        if(((i+1) % 3) == 0){
            printf("\n");

        }
        printf("\n");
    }
}

#endif
