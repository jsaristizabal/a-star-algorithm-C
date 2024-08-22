#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define PATH 100
#define MAX_NEIGHBORS 4


typedef struct {
    int row;
    int col;
    int xParent;
    int yParent;
    bool bObstacle;
    bool bVisited;
    int fCost;
    int hCost;    
} sNode;

typedef struct {
    int priority;
    int node;
} sPriorityQueue;






//------------------------------------------VARIABLES------------------------------------------
sNode neighbors[MAX_NEIGHBORS];
sNode startN = {4,0};
sNode goalN = {4,4};
sNode currentN = {0, 0}; // Nodo actual para la prueba

int sizeRows = 5;
int sizeCols = 5;
int prob = 2;

sNode nodesMatrix[MAX_ROWS][MAX_COLS];
sNode openQueue[PATH];
sNode closedQueue[PATH];


int count = 0;

int matrix[MAX_ROWS][MAX_COLS] = {0};
//------------------------------------------------------------------------------------



int manhattan_Dist(sNode *p1,sNode *p2){
    int x1 = p1->col;
    int y1 = p1->row;
    
    int x2 = p2->col;
    int y2 = p2->row;

    int dist = abs(x2 - x1) + abs(y2 - y1);
    
    return (dist);
}

int h_cost(sNode *point){
    // h(n): Es la funcion heuristica que estima el camino mas corto desde n hasta el FINAL

    return manhattan_Dist(point,&goalN);
}

int g_cost(sNode *point){
    // g(n): es el costo del camino desde el INICIO hasta n
    return manhattan_Dist(&startN,point);
}

int f_cost(sNode *point){
    return (g_cost(point) + h_cost(point));
}


void init_grid(sNode mtrx[MAX_ROWS][MAX_COLS]){

    for (int i = 0; i < sizeRows; i++){
        for (int j = 0; j < sizeCols; j++){
            //assign coordinates (i,j)
            mtrx[i][j].row = i;
            mtrx[i][j].col = j;
            mtrx[i][j].xParent = 0;
            mtrx[i][j].yParent = 0;
            mtrx[i][j].bVisited = false;
            mtrx[i][j].fCost = 0;
            mtrx[i][j].hCost = 0;

            if (rand() % 10 < prob){
                mtrx[i][j].bObstacle = true;                
            }
            else{
                mtrx[i][j].bObstacle = false;
            }
        }   
    }
}


void print_grid(sNode mtrx[MAX_ROWS][MAX_COLS], sNode *start,sNode *goal){
    printf("Matrix (%d,%d):\n",sizeRows,sizeCols);

    for (int i = 0; i < sizeRows; i++){
        for (int j = 0; j < sizeCols; j++){

            if((mtrx[i][j].row == start->row) && (mtrx[i][j].col == start->col)){
                mtrx[i][j].bObstacle = false;
                printf("S ");
            }

            else if((mtrx[i][j].row == goal->row) && (mtrx[i][j].col == goal->col)){
                mtrx[i][j].bObstacle = false;
                printf("G ");

            }

            else if (mtrx[i][j].bObstacle == false){
                printf("\u00B7 ");
            }
            else if(mtrx[i][j].bObstacle == true){
                printf("X ");
            }


        }
        printf("\n");
    }
}

void updateNeighbors(sNode *current, sNode matrx[MAX_ROWS][MAX_COLS], sNode neighbors[MAX_NEIGHBORS], int *count){
    int x = current->row;
    int y = current->col;
    
    *count = 0;

    printf("Current (%d,%d)\n",x,y);

    if( x+1 < sizeRows && (matrx[x + 1][y].bObstacle == false)){//down
        neighbors[*count].row = x+1;
        neighbors[*count].col = y;
        (*count)++;
    }
    if( x > 0 && (matrx[x - 1][y].bObstacle == false)){//up
    neighbors[*count].row = x - 1;
    neighbors[*count].col = y;
    (*count)++;
    }

    if( y + 1 < sizeCols && (matrx[x][y + 1].bObstacle == false)){//right
    neighbors[*count].row = x;
    neighbors[*count].col = y + 1;
    (*count)++;
    }
    if( y > 0 && (matrx[x][y - 1].bObstacle == false)){//left
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
        printf("gcost %d\n",g_cost(&neighbors[i]));
        printf("hcost %d\n",h_cost(&neighbors[i]));
        printf("fcost %d\n",f_cost(&neighbors[i]));

    }
}



void aStar(sNode matrx[MAX_ROWS][MAX_COLS]){

    int temp_f = 0;
    int temp_g = 0;
    int temp_h = 0;

    updateNeighbors(&currentN, nodesMatrix, neighbors, &count);


    

    do{
        for (int i = 0; i < count; i++) {
            temp_f = f_cost(&neighbors[i]);
            temp_g = h_cost(&neighbors[i]);
            temp_h = g_cost(&neighbors[i]);
            }

        
        /* code */
    } while (goalN.row != currentN.row && goalN.col != currentN.col);
    




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

void main(){
    clear_screen();
    srand(time(NULL));
    // srand(12345); //Puedes cambiar 12345 por cualquier otro número


    init_grid(nodesMatrix);
    print_grid(nodesMatrix,&startN,&goalN);

    updateNeighbors(&startN, nodesMatrix, neighbors, &count);
    print_neighbors(neighbors, count);

    // printf("prueba manhattan %d:\n",manhattan_Dist(&currentN,&goalN));
}
