#pragma once
#include <stdbool.h> 
#include "row.h"


void _addWord(Row *row, Word word)
{
    insert(&row->row_words, word);
    row->num_elements += 1;
}

void addInt(Row *row, long long int int_number)
{
    Word new_word;
    new_word.data_type = INTIGER;
    new_word.intiger = int_number;

    _addWord(row, new_word);
}

void addFloat(Row *row, long double floating_point)
{
    Word new_word;
    new_word.data_type = FLOATING_POINT;
    new_word.floating_point = floating_point;

    _addWord(row, new_word);
}

void addNotANumber(Row *row, char *not_a_number)
{
    Word new_word;
    new_word.data_type = NOT_A_NUMBER;
    new_word.not_a_number = not_a_number;

    _addWord(row, new_word);
}

bool compareTwoRows(Row row1, Row row2)
{
    if (row1.num_elements != row2.num_elements)
        return false;
    else
        return compareTrees(row1.row_words, row2.row_words);
}
