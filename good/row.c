#pragma once
#include <stdbool.h> 
#include "row.h"


void addWord(Row *row, Word word)
{
    insert(&row->row_words, word);
    row->num_elements += 1;
}

bool compareTwoRows(Row row1, Row row2)
{
    if (row1.num_elements != row2.num_elements)
        return false;
    else
        return compareTrees(row1.row_words, row2.row_words)
}
