#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "helper_functions.h"
#include "row.h"
#include "row_counter.h"

#define INITIAL_WORD_BUFFER_SIZE 1024

int main() 
{
    int current_input, previous_input = '\n';
    unsigned int row_number = 0;
    RowTree row_counter = NULL;

    int current_word_buffer_size = INITIAL_WORD_BUFFER_SIZE;
    char * word = (char *)malloc(current_word_buffer_size * sizeof(char));
    if (!word)
        exit(EXIT_FAILURE);
    int word_len = 0;

    Row *row = (Row *)malloc(sizeof(Row));
    if (!row)
        exit(EXIT_FAILURE);
    row->num_elements = 0;
    row->num_unique_elements = 0;
    row->row_words = NULL;

    while(true) 
    {
        current_input = getc(stdin);
        // check if comment or invalid row :
        // either contains '#' or ascii character not in range [33, 126]
        if ((
            (current_input == '#' && previous_input == '\n') || 
            current_input < 33 || current_input > 126) && (!isWhitespace(current_input) && (current_input != EOF)))
        {
            row_number += 1;
            if (current_input != '#')
                fprintf(stderr, "ERROR %d\n", row_number);

            while((current_input = getc(stdin)) != EOF)
                if (current_input == '\n')
                    break;

            removeAllWordTree(row->row_words);
            row->row_words = NULL;
            row->num_elements = 0;
            row->num_unique_elements = 0;
            word_len = 0;
            previous_input = '\n';

            continue;
        }

        if (isWhitespace(current_input) || current_input == EOF)
        {
            // if previous character was also a whitespace nothing to do
            // if previous character wasn't a whitespace, there is new word to proceed
            if (!isWhitespace(previous_input))
            {
                word[word_len] = '\0';
                proceedWord(row, word, word_len);
                word_len = 0;              
            }
            previous_input = current_input;
        }
        
        if(!isWhitespace(current_input) && current_input != EOF)
        {
            if (word_len > current_word_buffer_size - 1)
            {
                word = (char *)realloc(word, current_word_buffer_size * 2 * sizeof(char));
                if (!word)
                    exit(EXIT_FAILURE);
                current_word_buffer_size *= 2;
            }
            word[word_len] = (char)current_input;
            word_len += 1;
            previous_input = current_input;
            continue;
        }

        if (current_input == '\n' ||  current_input == EOF) 
        {
            row_number += 1;
            if (row->num_elements > 0)
            {
                // if true, only increase count and we don't new pointer
                if (insertRowTree(&row_counter, row, row_number))
                    removeAllWordTree(row->row_words);
                else
                {
                    row = (Row *)malloc(sizeof(Row));
                    if (!row)
                        exit(EXIT_FAILURE);
                }
                row->num_elements = 0;
                row->num_unique_elements = 0;
                row->row_words = NULL;
            }
            previous_input = '\n';
            if (current_input == EOF)
                    break;
        }
    }
    
    printRows(row_counter);
    removeAllRowTree(row_counter);
    free(word);
    free(row);
    exit(EXIT_SUCCESS);
}