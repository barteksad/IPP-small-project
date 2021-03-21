#pragma once
#include "word.h"
#include "row.h"

// rows are stored in BST
// RowNode is a tree node and RowTree is a pointer to this tree
struct RowNode; 

typedef struct RowNode* RowTree;

bool insertRowTree(RowTree *row_tree_ptr, Row *row, int row_number);

// traverse tree in order and writes pointers to all tree elements to the array 
int goDFSRowTree(RowTree t, RowTree *rows_groups, int current_num);

// compare function used to sort silimar lines by row number
int compareRowGroups(const void *lhs, const void *rhs);

void printRows(RowTree row_counter);

void removeAllRowTree(RowTree t);