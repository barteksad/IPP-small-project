#pragma once
#include "bintree.h"
#include "row.h"

struct RowNode; 

static int num_rows_groups = 0;

typedef struct RowNode* RowTree;

bool insertRowTree(RowTree *row_tree_ptr, Row *row, int row_number);

int goDFSRowTree(RowTree t, RowTree *rows_groups[], int current_num);

int compareRowGroups(const void *lhs, const void *rhs);

void printRows(RowTree row_counter);

void removeAllRowTree(RowTree t);