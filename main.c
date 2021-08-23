#include <stdio.h>
#include <stdlib.h>

#define ROWS 12
#define COLUMNS 12

int main()
{
    srand(getpid());

    char maze[ROWS][COLUMNS];
    int start_row;
    int start_column = 0;
    int end_row;
    int end_column = 11;

    int another_maze = 1;
    while(another_maze){
        eraseMaze(maze);
        mazeGenerator(maze, &start_row, &end_row);
        printMaze(maze);

        printf("\nDesea elegir ortra maze? (0 no si cualquier numero): ");
        scanf("%d", &another_maze);
    }
    mazeTraverse(maze, start_row, start_column);

    scanf("%d", &start_row);
}


int mazeTraverse(char maze[ROWS][COLUMNS], int actual_row, int actual_column){
    maze[actual_row][actual_column] = 'X';
    if(actual_column == 11){
        printf("\nLa solucion es la siguiente\n\n");
        printMaze(maze);
        return 1;
    }
    if(maze[actual_row][actual_column + 1] == '.'){
        if(!mazeTraverse(maze, actual_row, actual_column + 1)){
           maze[actual_row][actual_column + 1] = '.';
           return 0;
        }
    }
    else if(maze[actual_row + 1][actual_column] == '.' && maze[actual_row - 1][actual_column] == '.'){
        if(mazeTraverse(maze, actual_row + 1, actual_column)){
            printf("\nLa solucion es la siguiente\n\n");
            printMaze(maze);
            return 1;
        }
        else if(mazeTraverse(maze, actual_row - 1, actual_column)){
            maze[actual_row + 1][actual_column] == '.';
            printf("\nLa solucion es la siguiente\n\n");
            printMaze(maze);
            return 1;
        }
        else {
            maze[actual_row + 1][actual_column] == '.';
            maze[actual_row -1][actual_column] == '.';
            return 0;
        }
    }
    else if (maze[actual_row + 1][actual_column] == '.'){
        if(!mazeTraverse(maze, actual_row + 1, actual_column)){
            maze[actual_row + 1][actual_column] = '.';
            return 0;
        }
    }
    else if (maze[actual_row - 1][actual_column] == '.'){
        if(!mazeTraverse(maze, actual_row - 1, actual_column)){
            maze[actual_row - 1][actual_column] = '.';
            return 0;
        }
    }
    else {
        maze[actual_row][actual_column] = '.';
        return 0;
    }
}


void mazeGenerator(char maze[ROWS][COLUMNS],int *start_row, int *end_row){
    //srand(getpid());

    *start_row = rand() % 10 + 1;

    for(int column=0; column<COLUMNS; column+= 11){
        for(int row=0; row<ROWS; row++){
            maze[column][row] = '#';
        }
    }

    for(int row=0; row<ROWS; row+= 11){
        for(int column=0; column<COLUMNS; column++){
            maze[column][row] = '#';
        }
    }

    int random_row = *start_row;
    int random_column = 1;
    int random;
    while(random_column<COLUMNS-1){
        random = rand() % 10;
        if(random != 0){
            if (random_row < ROWS-2 && random_row > 1)
                random_row += rand() % 3 - 1;
            else if(random_row > 1)
                random_row -= 1;
            else
                random_row += 1;
        }
        else
            random_column += 1;

        maze[random_row][random_column] = '.';
    }
    *end_row = random_row;

    for(int i=1; i<ROWS-1; i++){
        for(int j=1; j<COLUMNS-1; j++){
            if(maze[i][j] != '.' && rand() % 10){
                maze[i][j] = '#';
            }
            else
                maze[i][j] = '.';
        }
    }

    maze[*start_row][0] = '.';
    maze[*start_row][1] = '.';
}


void printMaze(char maze[ROWS][COLUMNS]){
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLUMNS; j++){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

void eraseMaze(char maze[ROWS][COLUMNS]){
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLUMNS; j++){
            maze[i][j] = '#';
        }
    }
}
