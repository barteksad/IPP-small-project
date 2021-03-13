#pragma once
#include "bintree.h"

typedef struct Row
{
    Tree row_words;
    unsigned int num_elements;
} Row;

void _addWord(Row *row, Word word);

void addInt(Row *row, long long int int_number);

void addFloat(Row *row, long double floating_point);

void addNotANumber(Row *row, char *not_a_number);


bool compareTwoRows(Row row1, Row row2);

