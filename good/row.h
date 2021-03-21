#pragma once
#include <stdbool.h>
#include "word.h"

// Row keeps stored words in a BST
typedef struct Row
{
    WordTree row_words;
    unsigned int num_elements;
    unsigned int num_unique_elements;
} Row;

// return true if added word was new
// and false if it has already been present, then just increase its count
bool addWord(Row *row, Word word);

// creates struc for float and calls addWord
void addFloat(Row *row, long double floating_point);

// creates struc for not a number and calls addWord
bool addNotANumber(Row *row, char *not_a_number);

// compares two rows
// row1 < row2 if:
// num elements in row1 < num elements in row2
// iterate : sorted words or its counts in row1 < sorted words or its counts in row2
enum CompareResult compareTwoRows(Row row1, Row row2);

