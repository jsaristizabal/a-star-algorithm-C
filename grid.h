// grid.h
#ifndef GRID_H
#define GRID_H


typedef struct Node{
    int row;
    int col;
    int cost;                //
    int heuristic;          //heuristic
    struct Node *parent;    //previous node
}Node;


// Matrix struct
typedef struct {
    int rows;
    int cols;
    int **data; // Pointer to a pointer for 2D matrix
    Node *start;
    Node *goal;
} Grid;




//Node structure


// Matrix functions
void create_initial_grid(Grid *grid, int prob);
void print_grid(const Grid *grid);
void free_grid(Grid *grid);
int getValue(const char *prompt, int low, int high);

Node* create_node(int row, int col, int cost, int heuristic, Node *parent);
void free_node(Node *node);

#endif // GRID_H