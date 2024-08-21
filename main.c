#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

int main() {

    srand(time(NULL)); // Inicializar la semilla aleatoria
    // srand(123); // Inicializar la semilla aleatoria
    
    Grid grid;
    int prob;

    grid.cols=20;
    grid.rows=10;
    prob = 2;

    // grid.rows = getValue("Ingrese el tamaño m de la matriz (10-60): ",10,60);
    // grid.cols = getValue("Ingrese el tamaño n de la matriz (10-128): ",10,128);
    // prob = getValue("Ingrese la probabilidad de obstácilos: ",0,10);
    
    // Crear la matriz
    create_initial_grid(&grid, prob);

    printf("Start coordinates: (%d, %d)\n", grid.start->row, grid.start->col);
    printf("Goal coordinates: (%d, %d)\n", grid.goal->row, grid.goal->col);
    
    // Imprimir la matriz
    printf("Matriz generada:\n");
    print_grid(&grid);
    
    // Liberar la memoria
    free_grid(&grid);
    
    return 0;
}
