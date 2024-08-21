#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Matrix struct
typedef struct {
    int rows;
    int cols;
} Grid;

//Node struct
typedef struct Node {
    int row;         // Row coordinate of the node in the grid
    int col;         // Column coordinate of the node in the grid
    int cost;        // Accumulated cost to reach this node from the start
    int heuristic;   // Estimated cost to reach the goal from this node
    int parent;      // Index or reference to the parent node
} Node;


// Function to clear the terminal screen
void clear_screen() {
    // Check for operating system
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif
}


void create_grid(Grid grid, int matrix[MAX_ROWS][MAX_COLS], int prob){
    //probability of obstacle
    //init matrix
    for (int i = 0; i < grid.rows; i++){
        for (int j = 0; j < grid.cols; j++){
            matrix[i][j] = (rand() % 10 < prob) ? 1 : 0;
        }   
    }
}

void print_grid(Grid grid, int matrix[MAX_ROWS][MAX_COLS]){
    printf("Matrix (%d,%d):\n",grid.rows,grid.cols);

    for (int i = 0; i < grid.rows; i++){
        for (int j = 0; j < grid.cols; j++){
            printf("%d",matrix[i][j]);
        }
        printf("\n");
    }
}

int getValue(const char *prompt, int min,int max) {
    int input = 0;
    int readResult = 0;

    while (1) {
        printf("%s", prompt); // Display the prompt message
        readResult = scanf("%d", &input); // Read integer input and store the result

        if (readResult != 1) { // Check if the input was not a valid integer
            printf("Ingresa un valor valido\n");
        } 
        else if (input < min || input > max) { // Check if the input is within the allowed range
            printf("El valor no se encuentra en el rango\n");
        } 
        else {
            return input; // Return the valid input
        }
    }
}


int main() {
    // Initialize grid with matrix dimensions
    clear_screen();

    // srand(time(NULL));
    srand(12345); // Puedes cambiar 12345 por cualquier otro número
    Grid grid;
    int matrix[MAX_ROWS][MAX_COLS] = {0};

    // Define matrix size
    grid.rows = getValue("Ingrese el tamaño m de la matriz (10-100): ",10,MAX_ROWS);
    grid.cols = getValue("Ingrese el tamaño n de la matriz (10-100): ",10,MAX_COLS);
    int prob = getValue("Ingresa la probabilidad de obstaculos (0-3): ",0,3);
    // grid.cols = 5;
    // grid.rows = 10;
    // int prob = 2;


    create_grid(grid, matrix, prob);

    print_grid(grid,matrix);

    return 0;
}
