// grid.h
#ifndef GRID_H
#define GRID_H

// Matrix struct
typedef struct {
    int rows;
    int cols;
    int **data; // Pointer to a pointer for 2D matrix
    Node *start;
    Node *goal;
} Grid;

//Node struct

typedef struct Node{
    int row;
    int col;
    int cost;                //
    int heuristic;          //heuristic
    struct Node *parent;    //previous node
}Node;



//Node structure


// Matrix functions
void create_initial_grid(Grid *grid, int prob);
void print_grid(const Grid *grid);
void free_grid(Grid *grid);
int getValue(const char *prompt, int low, int high);

#endif // GRID_H