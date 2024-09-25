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
    int xParent;
    int yParent;
    bool bObstacle;
    bool bVisited;
    int fCost;
    int hCost;    
} sNode;

//------------------------------------------VARIABLES GLOBALES------------------------------------------
sNode neighborsList[MAX_NEIGHBORS];
sNode startN = {4,1};
sNode goalN = {4,9};

int bestIndex = 0;



int openLsize = 0;
int fCosts[MAX_ROWS] = {0};
sNode openL[MAX_ROWS] = {0};
bool closedL[MAX_ROWS][MAX_COLS] = {false};//Lista de nodos cerrados


int sizeRows = 10;
int sizeCols = 10;
int prob = 0;

sNode nodesMatrix[MAX_ROWS][MAX_COLS];

int countNeighbors = 0;



int matrix[MAX_ROWS][MAX_COLS] = {0};
//------------------------------------------------------------------------------------


void searchBestF(void);
void rmFromOpenL(sNode* nodeToRM);



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
    printf("Matrix %dx%d\t",sizeRows,sizeCols);
    printf("Start= (%d,%d):\t",start->row,start->col);
    printf("Goal= (%d,%d):\n",goal->row,goal->col);

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

    printf("Nodo actual (%d,%d)-----------------------------------------------------\n",x,y);

    if( x+1 < sizeRows && (matrx[x + 1][y].bObstacle == false) && (matrx[x + 1][y].bVisited == false)){//down
        neighbors[*count].row = x+1;
        neighbors[*count].col = y;
        (*count)++;
    }
    if( x > 0 && (matrx[x - 1][y].bObstacle == false) && (matrx[x - 1][y].bVisited == false)){//up
    neighbors[*count].row = x - 1;
    neighbors[*count].col = y;
    (*count)++;
    }

    if( y + 1 < sizeCols && (matrx[x][y + 1].bObstacle == false) && (matrx[x][y + 1].bVisited == false)){//right
    neighbors[*count].row = x;
    neighbors[*count].col = y + 1;
    (*count)++;
    }
    if( y > 0 && (matrx[x][y - 1].bObstacle == false) && (matrx[x][y - 1].bVisited == false)){//left
    neighbors[*count].row = x;
    neighbors[*count].col = y - 1;
    (*count)++;
    }
    // printf("Neighbors Count (%d)\n",*count);
}


// Función para imprimir la lista de vecinos
void print_neighbors(sNode neighbors[MAX_NEIGHBORS], int count) {
    printf("Neighbors (%d):\n", count);
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", neighbors[i].row, neighbors[i].col);
        printf("gcost %d\n",g_cost(&neighbors[i]));
        printf("hcost %d\n",h_cost(&neighbors[i]));
        printf("fcost %d\n",f_cost(&neighbors[i]));
    }
}

//------------------------------------------------------ALGORITMO PRINCIPAL------------------------------------------------------

void aStar(sNode matrx[MAX_ROWS][MAX_COLS]){

    printf("A*...\n");
    

    sNode currentN = startN; // Nodo actual

    openL[openLsize++] = startN; //agregamos el nodo inicial a la lista abierta

    int iteration = 0; // Variable de control para las iteraciones
    int maxIterations = 11; // Establece el número máximo de iteraciones
    

    while (openLsize >0 && iteration < maxIterations){


        printf("\niteracion de while: %d \t",iteration);
        updateNeighbors(&currentN, matrx, neighborsList, &countNeighbors);//revisemos los vecinos
        print_neighbors(neighborsList, countNeighbors);
        
        //agregamos el vecino a la lista abierta
        for (int i = 0; i < countNeighbors; i++){
            if (closedL[neighborsList[i].row][neighborsList[i].col] == false){
                printf("agregando el vecino %d a la lista abierta: (%d,%d)\n",i,neighborsList[i].row,neighborsList[i].col);
                openL[openLsize++] = neighborsList[i];
            }

        }


        searchBestF();
        for (int i = 0; i < openLsize; i++){
            printf("Recorriendo OpenL: en nodo (%d,%d)\n",openL[i].row,openL[i].col);
        }

        printf("nodo (%d,%d)removido\n",currentN.row,currentN.col);
        printf("openLsize era : %d\n",openLsize);
    
        rmFromOpenL(&currentN);
        
        printf("openLsize ahora es: %d\n",openLsize);
        for (int i = 0; i < openLsize; i++){
            printf("Recorriendo OpenL: en nodo (%d,%d)\n",openL[i].row,openL[i].col);
        }
        
        //nos desplazamos al nodo con costo mas bajo y asignamos la procedencia
        sNode *nextNode = &openL[bestIndex];
        nextNode->xParent = currentN.row;
        nextNode->yParent = currentN.col;
        currentN = *nextNode;
        printf("Nos desplazamos a: (%d,%d) desde (%d,%d)\n",currentN.row,currentN.col,currentN.xParent,currentN.yParent);
        


        if (currentN.row == goalN.row && currentN.col == goalN.col) {
            printf("Goal reached!\n");
            printf("objetivo alcanzado en %d iteraciones\n",iteration);
            // Aquí deberías reconstruir y mostrar el camino
            return;
        }


        iteration++;//incrementar la variable de control
        }


        // Si el bucle termina por alcanzar maxIterations
        if (iteration >= maxIterations) {
            printf("Max iterations reached: %d\n", maxIterations);
        }
}




void rmFromOpenL(sNode* nodeToRM){
    int indexToRm = -1;
    // printf("Vamos a eliminar (%d,%d) de la lista abierta\n",nodeToRM->row,nodeToRM->col);
    // printf("openLsize: %d\n",openLsize);
    closedL[nodeToRM->row][nodeToRM->col] = true;
    nodeToRM->bVisited = true;

    for (int i = 0; i < openLsize; i++){
        // printf("Recorriendo OpenL: en nodo (%d,%d)\n",openL[i].row,openL[i].col);
    }

    for (int i = 0; i < openLsize; i++){
        if (openL[i].row == nodeToRM->row && openL[i].col == nodeToRM->col){
            indexToRm = i;
            break;
        }        
    }

    // printf("Nodo (%d,%d) Eliminado de la lista abierta\n",nodeToRM->row,nodeToRM->col);
    
    if (indexToRm != -1){
        if (indexToRm < openLsize -1){
            openL[indexToRm] = openL[--openLsize];
        }
        else{
            --openLsize;
        }
    }
    // printf("openLsize: %d\n",openLsize);

    for (int i = 0; i < openLsize; i++){
        // printf("Recorriendo OpenL: en nodo (%d,%d)\n",openL[i].row,openL[i].col);
    }

}

void searchBestF(void){
    
    bestIndex = 0;  //reiniciamos la variable para empezar la busqueda
    //recorremos OpenL
    for (int i = 1; i < openLsize; i++){
        //Comparamos los f cost para buscar el mejor
        if (f_cost(&openL[i]) <= f_cost(&openL[bestIndex])){
            bestIndex = i;  //guardamos el valor del menor fcost
        }
    }
    printf("El mejor fcost es %d con coordenada (%d,%d)\n",f_cost(&openL[bestIndex]),openL[bestIndex].row,openL[bestIndex].col);
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
}
