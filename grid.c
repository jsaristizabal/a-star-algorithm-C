// grid.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"


//create node
Node* create_node(int row, int col, int cost, int heuristic, Node *parent){
    Node *node = (Node*)malloc(sizeof(Node));
    
    node->row = row;
    node->col = col;
    node->heuristic = heuristic;
    node->parent = parent;
    node->cost = cost;
    
    return node;
}




//creating initial matrix
void create_initial_grid(Grid* matrix, int prob){
    matrix->data = (int**)malloc(matrix->rows * sizeof(int*));
    
    for (int m = 0; m < matrix->rows ; m++){
        
        matrix->data[m] = (int *)malloc(matrix->cols * sizeof(int));

        for(int n = 0; n < matrix->cols ; n++){
            matrix->data[m][n] = (rand() % 10 < prob) ? 1 : 0;

            /*This is the same*/
            // if( rand() % 10 < prob){
            //     matrix->data[m][n] = 1; //obstacle
            // }
            // else{
            //     matrix->data[m][n] = 0; //free cell
            // }
        }
    }
    int startX,startY,goalX,goalY;
    //Place start and goal points
    do{
        startX = rand() % matrix->rows;
        startY = rand() % matrix->cols;
    }while (matrix->data[startX][startY] == 1);


    //place the node S
    matrix->start = create_node(startX,startY,0,0,NULL);
    // printf("Start coordinates: (%d, %d)\n", matrix->start->row, matrix->start->col);

    do{
        goalX = rand() % matrix->rows;
        goalY = rand() % matrix->cols;
    } while ((goalX == startX && goalY == startY ) || (matrix->data[goalX][goalY] ==1));

    //Place the node G

    matrix->goal = create_node(goalX,goalY,0,0,NULL);
    


}


void print_grid(const Grid *matrix){
    for(int m = 0; m < matrix->rows ; m++){
        for(int n = 0; n < matrix->cols ; n++){

            if(m == matrix->start->row && n == matrix->start->col){
                printf("S ");

            }
            else if(m == matrix->goal->row && n == matrix->goal->col){
                printf("G ");
            }
            else if(matrix->data[m][n] == 0){
                printf("\u00B7 ");              //Middle point using UNICODE
            }
            else if (matrix->data[m][n] == 1){
                printf("X ");
            }

        }
        printf("\n");
    }

}



int getValue(const char *prompt, int low, int high){
    int value;
    int result;

    while(1){
        printf("%s",prompt);
        result = scanf("%d",&value);
        
        if(result != 1){
            printf("ingrese un numero valido\n");
        }
        else if(value < low || value > high){
            printf("El valor no se encuentra en el rango\n");
        }
        else{
            return value;
        }


    }


}

// Función para liberar la memoria de la matriz
void free_grid(Grid *grid) {
    for (int i = 0; i < grid->rows; i++) {
        free(grid->data[i]);
    }
    free(grid->data);
}