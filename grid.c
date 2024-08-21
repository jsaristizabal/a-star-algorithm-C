// grid.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

//creating initial matrix

void create_initial_grid(Grid* matrix, int prob){
    matrix->data = (int**)malloc(matrix->rows * sizeof(int*));
    
    for (int m = 0; m< matrix->rows; m++){
        matrix->data[m] = (int *)malloc(matrix->cols * sizeof(int));

        for(int n = 0; n < matrix->cols ; n++){

            if( rand() % 10 < prob){
                matrix->data[m][n] = 1; //obstacle
            }

            else{
                matrix->data[m][n] = 0; //free cell
            }

        }
    }
}


void print_grid(const Grid *matrix){
    for(int m = 0; m < matrix->rows ; m++){
        for(int n = 0; n < matrix->cols ; n++){
            
            if(matrix->data[m][n] == 0){
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