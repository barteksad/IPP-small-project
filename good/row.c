#include <stdbool.h> 
#include "row.h"

void addWord(Row *row, Word word, int word_len)
{
    row->num_elements += 1;
<<<<<<< HEAD
    bool if_new = insertWordTree(&row->row_words, word);
    if (if_new)
        row->num_unique_elements += 1;
    
    return if_new;
=======
    bool if_already_exsists = insertWordTree(&row->row_words, word, word_len);
    if (!if_already_exsists)
        row->num_unique_elements += 1;    
>>>>>>> try_buffer_again
}

void addFloat(Row *row, long double floating_point)
{
    Word new_word;
    new_word.data_type = FLOATING_POINT;
    new_word.floating_point = floating_point;
    addWord(row, new_word, -1);
}

void addNotANumber(Row *row, char *not_a_number, int word_len)
{
    Word new_word;
    new_word.data_type = NOT_A_NUMBER;
    new_word.not_a_number = not_a_number;
    addWord(row, new_word, word_len);
}

// najpierw porównuje po liczbie elementow i liczbie unikatowych elementów
// jeśli równe wywołuje compareTreesWordTree która porównuje szczegółowe dwa BST zawierające słowa
enum CompareResult compareTwoRows(Row row1, Row row2)
{
    if (row1.num_elements < row2.num_elements || row1.num_unique_elements < row2.num_unique_elements)
        return SMALLER;
    else if (row1.num_elements > row2.num_elements || row1.num_unique_elements > row2.num_unique_elements)
        return BIGGER;
    else
    {
        return compareTreesWordTree(row1.row_words, row2.row_words, row2.num_unique_elements);
    }
}
