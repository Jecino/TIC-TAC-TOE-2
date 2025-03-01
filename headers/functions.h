#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Gamemanager creation
typedef struct{
    int lastPos, choosedPos, lastPos2, choosedPos2, lastPlayer, nextPlayer, exited;
    char winned[9];
    int PC;

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

    fprintf(save, "%d %d %d %d %d %d %d\n", gamemanager.choosedPos2, gamemanager.choosedPos, gamemanager.lastPlayer, gamemanager.lastPos2, gamemanager.lastPos, gamemanager.nextPlayer, gamemanager.PC);

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

    fscanf(load, "%d %d %d %d %d %d %d\n", &gamemanager -> choosedPos2, &gamemanager -> choosedPos, &gamemanager -> lastPlayer, &gamemanager -> lastPos2, &gamemanager -> lastPos, &gamemanager -> nextPlayer, &gamemanager->PC);

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