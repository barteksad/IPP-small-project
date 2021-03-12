#pragma once
#include "bintree.h"

typedef struct
{
    Tree row_words;
    unsigned int num_elements;
} Row;


void addWord(Row *row, Word word);

bool compareTwoRows(Row row1, Row row2);

