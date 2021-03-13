#pragma once
#include "bintree.h"

typedef struct Row
{
    Tree row_words;
    unsigned int num_elements;
} Row;

bool _addWord(Row *row, Word word);

void addInt(Row *row, unsigned long long int int_number);

void addFloat(Row *row, long double floating_point);

bool addNotANumber(Row *row, char *not_a_number);


bool compareTwoRows(Row row1, Row row2);

