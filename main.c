#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_NEIGHBORS 4


typedef struct {
    int row;
    int col;
} sNode;

typedef struct {
    int rows;
    int cols;
} sGrid;



//------------------------------------------VARIABLES------------------------------------------
sGrid grid;
sNode startN = {-1,-1};
sNode goalN = {-1,-1};
sNode neighbors[MAX_NEIGHBORS];
sNode current = {2, 3}; // Nodo actual para la prueba
int sizeX = 0;
int sizeY = 0;
int prob = 0;
int count = 0;

int matrix[MAX_ROWS][MAX_COLS] = {0};
//------------------------------------------------------------------------------------



float manhattan_Dist(sNode *p1,sNode *p2){
    int x1 = p1->col;
    int y1 = p1->row;
    
    int x2 = p2->col;
    int y2 = p2->row;

    float dist = abs(x2-x1) + abs(y2-y1);
    
    return (dist);
}

float h_cost(sNode *point){

    return manhattan_Dist(point,&goalN);
}

float g_cost(sNode *point){
    return manhattan_Dist(&startN,point);
}

float f_cost(sNode *point){
    return (g_cost(point)+h_cost(point));
}


void init_grid(int matrx[MAX_ROWS][MAX_COLS]){

    for (int i = 0; i < grid.rows; i++){
        for (int j = 0; j < grid.cols; j++){
            matrx[i][j] = (rand() % 10 < prob) ? 1 : 0;//place 0 and 1 for obstacles and free node
        }   
    }
}

void updateNeighbors(sNode *current,int matrx[MAX_ROWS][MAX_COLS], sNode neighbors[MAX_NEIGHBORS], int *count){
    int x = current->row;
    int y = current->col;
    
    *count = 0;

    printf("Current (%d,%d)\n",current->row,current->col);

    if( x+1 < sizeX && !(matrix[x + 1][y] == 1)){//down
        neighbors[*count].row = x+1;
        neighbors[*count].col = y;
        (*count)++;
    }
    if( x > 0 && !(matrix[x - 1][y] == 1)){//up
    neighbors[*count].row = x - 1;
    neighbors[*count].col = y;
    (*count)++;
    }

    if( y + 1 < sizeY && !(matrix[x][y + 1] == 1)){//right
    neighbors[*count].row = x;
    neighbors[*count].col = y + 1;
    (*count)++;
    }
    if( y > 0 && !(matrix[x][y - 1] == 1)){//left
    neighbors[*count].row = x;
    neighbors[*count].col = y - 1;
    (*count)++;
    }
}

// Función para imprimir la lista de vecinos
void print_neighbors(sNode neighbors[MAX_NEIGHBORS], int count) {
    printf("Neighbors:\n");
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", neighbors[i].row, neighbors[i].col);
    }
}

void placePoint(int matrx[MAX_ROWS][MAX_COLS], sNode *start, sNode *goal){
    
    //if start point not provided, generate randomly
    if (start->row == -1 || start->col == -1){
        do{
            start->row = rand() % grid.rows;
            start->col = rand() % grid.cols;
        } while (matrx[start->row][start->col] == 1);
    }

    //if start point not provided, generate randomly
    if (goal->row == -1 || goal->col == -1){
        do{
            goal->row = rand() % grid.rows;
            goal->col = rand() % grid.cols;
        } while ( (matrx[start->row][start->col] == 1) || (goal->row == start->row && goal->col==start->col));
    }

        // Place points in the matrix
    matrx[start->row][start->col] = 2; // Start point
    matrx[goal->row][goal->col] = 3;   // Goal point

    printf("Start point: (%d, %d)\n", start->row, start->col);
    printf("Goal point: (%d, %d)\n", goal->row, goal->col);

}



void print_gridNumbers(int matrx[MAX_ROWS][MAX_COLS]){
    printf("Matrix (%d,%d):\n",grid.rows,grid.cols);

    for (int i = 0; i < grid.rows; i++){
        for (int j = 0; j < grid.cols; j++){
            printf("%d",matrx[i][j]);
        }
        printf("\n");
    }
}

void print_grid(int matrx[MAX_ROWS][MAX_COLS]){
    printf("Matrix size %dx%d:\n",grid.rows,grid.cols);

    for (int i = 0; i < grid.rows; i++){
        for (int j = 0; j < grid.cols; j++){

            if (matrx[i][j] == 0){
                printf("\u00B7 ");
            }
            else if(matrx[i][j] == 1){
                printf("X ");
            }
            else if(matrx[i][j] == 2){
                printf("S ");
            }
            else if(matrx[i][j] == 3){
                printf("G ");
            }
            else if(matrx[i][j] == 4){
                printf("@ ");
            }
        }
        printf("\n");
    }
}

void aStar(int matrx[MAX_ROWS][MAX_COLS]){

    
}

// Function to clear the terminal screen
void clear_screen() {
    // Check for operating system
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif
}

int main(){
    clear_screen();
    srand(time(NULL));
    // srand(12345); //Puedes cambiar 12345 por cualquier otro número
    sizeX = 5;
    sizeY = 5;
    prob = 2;
    grid.rows = sizeX;
    grid.cols = sizeY;
    init_grid(matrix);
    placePoint(matrix,&startN,&goalN);
    print_grid(matrix);
    updateNeighbors(&goalN, matrix, neighbors, &count);
    print_neighbors(neighbors, count);
    return 0;
}
