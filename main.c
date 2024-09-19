#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_NEIGHBORS 4


typedef struct {
    float row;
    float col;
    float xParent;
    float yParent;
    bool bObstacle;
    bool bVisited;
    float fCost;
    float hCost;    
} sNode;

//------------------------------------------VARIABLES GLOBALES------------------------------------------
sNode neighbors[MAX_NEIGHBORS];
sNode startN = {4,1};
sNode goalN = {4,5};



int openLsize = 0;
int fCosts[MAX_ROWS] = {0};
sNode openL[MAX_ROWS] = {0};


int sizeRows = 10;
int sizeCols = 10;
int prob = 0;

sNode nodesMatrix[MAX_ROWS][MAX_COLS];



int count = 0;

int matrix[MAX_ROWS][MAX_COLS] = {0};
//------------------------------------------------------------------------------------



float manhattan_Dist(sNode *p1,sNode *p2){
    float x1 = p1->col;
    float y1 = p1->row;
    
    float x2 = p2->col;
    float y2 = p2->row;

    float dist = abs(x2 - x1) + abs(y2 - y1);
    
    return (dist);
}

float h_cost(sNode *point){
    // h(n): Es la funcion heuristica que estima el camino mas corto desde n hasta el FINAL

    return manhattan_Dist(point,&goalN);
}

float g_cost(sNode *point){
    // g(n): es el costo del camino desde el INICIO hasta n
    return manhattan_Dist(&startN,point);
}

float f_cost(sNode *point){
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
    printf("Matrix %dx%d\t",sizeRows,sizeCols);
    printf("Start= (%.1f,%.1f):\t",start->row,start->col);
    printf("Goal= (%.1f,%.1f):\n",goal->row,goal->col);

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

    printf("CurrentN (%d,%d)\n",x,y);

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
    printf("Neighbors Count (%d)\n",*count);
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

    printf("A*...\n");
    

    sNode currentN = startN; // Nodo actual

    bool closedL[MAX_ROWS][MAX_COLS] = {false};//Lista de nodos cerrados
    
    openL[openLsize++] = startN; //agregamos el nodo inicial a la lista abierta
    
    updateNeighbors(&openL[0], nodesMatrix, neighbors, &count);//revisemos los vecinos en la lista abierta iteracion 1

    //agregamos el vecino a la lista abierta
        for (int i = 0; i < count; i++) {
        openL[openLsize++] = neighbors[i];//si todos los vecinos son viables, en este punto openLsize es 5(4 vecinos y 1 start)
    }


    //recorremos la lista abierta para buscar el menor fcost   entre los vecinos, por esto i=1
    int bestIndex = 0;
    for (int i = 1; i < openLsize; i++){

        printf("valor de i (%d)\n",i);
        printf("coordenada (%.1f,%.1f)\n",openL[i].row,openL[i].col);
        
        printf("fcost %.1f\n\n",f_cost(&openL[i]));

        //almacenamos el mejor fcost
        if (f_cost(&openL[i]) <= f_cost(&openL[bestIndex])){
            bestIndex = i;  //guardamos el valor del menor fcost
            printf("valor de mejor index (%d)\n",bestIndex);
        }
        
    }

    //agregamos el nodo inicial a la lista cerrada ya que fue explorado
    closedL[(int)currentN.row][(int)currentN.col] = true;

    
    //nos desplazamos al nodo con costo mas bajo y asignamos la procedencia
    sNode *nextNode = &openL[bestIndex];
    nextNode->xParent = currentN.row;
    nextNode->yParent = currentN.col;
    printf("coordenada ANTES de moverse (%.1f,%.1f)\n",currentN.row, currentN.col);
    currentN = *nextNode;



    printf("coordenada DESPUES de moverse (%.1f,%.1f)\n",currentN.row, currentN.col);




    if (currentN.row == goalN.row && currentN.col == goalN.col) {
        printf("Goal reached!\n");
        // Aquí deberías reconstruir y mostrar el camino
        return;
    }

    // updateNeighbors(&openL[0], nodesMatrix, neighbors, &count);//revisemos los vecinos en la lista abierta iteracion 1

    printf("coordenada despues de moverse y eliminar el nodo inicial (%.1f,%.1f)\n",openL[0].row,openL[0].col);
    
}


void rmFromOpenL(sNode nodeToRM){
    int indexToRm = -1;
    for (int i = 0; i < openLsize; i++){
        if (openL[i].row == nodeToRM.row && openL[i].col == nodeToRM.col){
            indexToRm = i;
            break;
        }        
    }

    if (indexToRm != -1){
        if (indexToRm < openLsize -1){
            openL[indexToRm] = openL[--openLsize];
        }
        else{
            --openLsize;
        }

    }

}


void checkCosts(void){
    int bestIndex = 0;
    for (int i = 0; i < openLsize; i++) {
        printf("iteracion (%.1f)\n", i);

        if (f_cost(&openL[i])){
            /* code */
        }
        
        
        printf("(%.1f, %.1f)\n", neighbors[i].row, neighbors[i].col);
        printf("gcost %.1f\n",g_cost(&neighbors[i]));
        printf("hcost %.1f\n",h_cost(&neighbors[i]));
        printf("fcost %.1f\n\n",f_cost(&neighbors[i]));
    }
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

void main(){
    clear_screen();
    srand(time(NULL));
    // srand(12345); //Puedes cambiar 12345 por cualquier otro número

    // sizeRows = getValue("Ingrese el tamaño m de la matriz (10-100): ",10,MAX_ROWS);
    // sizeCols = getValue("Ingrese el tamaño n de la matriz (10-100): ",10,MAX_COLS);
    // prob = getValue("Ingresa la probabilidad de obstaculos (0-3): ",0,3);


    init_grid(nodesMatrix);
    print_grid(nodesMatrix,&startN,&goalN);
    aStar(nodesMatrix);

    // updateNeighbors(&startN, nodesMatrix, neighbors, &count);
    // print_neighbors(neighbors, count);

    // printf("prueba manhattan %d:\n",manhattan_Dist(&currentN,&goalN));
}
