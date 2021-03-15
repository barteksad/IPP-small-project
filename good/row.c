#pragma once
#include <stdbool.h> 
#include "row.h"


bool addWord(Row *row, Word word)
{
    row->num_elements += 1;
    bool if_already_exsists = insertWordTree(&row->row_words, word);
    if (!if_already_exsists)
        row->num_unique_elements += 1;
    
    return if_already_exsists;
}

void addFloat(Row *row, long double floating_point)
{
    Word new_word;
    // printf("%Lf ", new_word.floating_point);
    new_word.data_type = FLOATING_POINT;
    new_word.floating_point = floating_point;
    // printf("%Lf ", new_word.floating_point);
    addWord(row, new_word);
}

bool addNotANumber(Row *row, char *not_a_number)
{
    Word new_word;
    new_word.data_type = NOT_A_NUMBER;
    new_word.not_a_number = not_a_number;
    return addWord(row, new_word);
}

enum CompareResult compareTwoRows(Row row1, Row row2)
{
    if (row1.num_elements < row2.num_elements || row1.num_unique_elements < row2.num_unique_elements)
        return SMALLER;
    else if (row1.num_elements > row2.num_elements || row1.num_unique_elements > row2.num_unique_elements)
        return GREATER;
    else
    {
        // printf("Comparing %d %d %d %d\n", row1.num_elements, row2.num_elements, row1.num_unique_elements, row2.num_unique_elements);
        return compareTreesWordTree(row1.row_words, row2.row_words, row2.num_unique_elements);
    }
}
