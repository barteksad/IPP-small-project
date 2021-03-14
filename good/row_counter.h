#pragma once
#include "bintree.h"
#include "row.h"

struct RowNode; 

typedef struct RowNode* RowTree;

bool insertRowTree(RowTree *row_tree_ptr, Row *row, int row_number);

// void printRows(RowCounter *row_counter);

void removeAllRowTree(RowTree t);