#pragma once
#include "word.h"
#include "row.h"

// BST na wiersze
struct RowNode; 

typedef struct RowNode* RowTree;

// dodaje do BST na wiersze
// true - element już był, dopisujemy jego numer wiersza
// false - dodano nowy element
bool insertRowTree(RowTree *row_tree_ptr, Row *row, int row_number);

// przechodzi drzewo in order i zapisuje wskałniki do wierszy w danej tablicy
int goDFSRowTree(RowTree t, RowTree *rows_groups, int current_num);

// predykat do sortowania podobnych wierszy zgodnie ze specyfikacją
// wystarczy porównać nr poierwszego zapisanego wiersza w grupie
int compareRowGroups(const void *lhs, const void *rhs);

void printRows(RowTree row_counter);

void removeAllRowTree(RowTree t);