#pragma once
#include <stdbool.h>
#include "bintree.h"

typedef struct Row
{
    WordTree row_words;
    unsigned int num_elements;
    unsigned int num_unique_elements;
} Row;

bool addWord(Row *row, Word word);

void addFloat(Row *row, long double floating_point);

bool addNotANumber(Row *row, char *not_a_number);

enum CompareResult compareTwoRows(Row row1, Row row2);

