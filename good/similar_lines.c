#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "helper_functions.h"
#include "row.h"
#include "row_counter.h"


int main() 
{
    int current_input, previous_input = '\n';
    unsigned int row_number = 0;
    RowTree row_counter = NULL;

    size_t word_buffer_init_size = 128;
    size_t word_buffer_size = 128;
    size_t word_len = 0;
    char * word = (char *)malloc(word_buffer_init_size* sizeof(char));
    word[0] = '\0';

    Row *row = (Row *)malloc(sizeof(Row));
    row->num_elements = 0;
    row->num_unique_elements = 0;
    row->row_words = NULL;

    while(true) 
    {
        current_input = getc(stdin);

        // check if comment or invalid row :
        // either contains '#' or ascii character not in range [33, 126]
        if (((current_input == '#' && previous_input == '\n') || current_input < 33 || current_input > 126) && (!isWhitespace(current_input) && (current_input != EOF)))
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
            word[0] = '\0';
            previous_input = '\n';

            continue;
        }

        if (isWhitespace(current_input) && current_input != '\n')
        {
            // if previous character was also a whitespace nothing to do
            // if previous character wasn't a whitespace, there is new word to proceed
            if (!isWhitespace(previous_input))
            {
                if (proceedWord(row, word))
                {
                    word = (char *)malloc(word_buffer_init_size* sizeof(char));
                    word_buffer_size = word_buffer_init_size;
                    if (word == NULL)
                        exit(EXIT_FAILURE);
                }
                word_len = 0;
                word[0] = '\0';                     
            }
            previous_input = current_input;
            continue;
        }
        
        // if a not whitespace character then add to word string
        if(!isWhitespace(current_input) && current_input != EOF)
        {
            if (word_len >= word_buffer_size -1)
            {
                word = (char *)realloc(word, 2*word_buffer_size*sizeof(char));
                word_buffer_size*=2;
                if (word == NULL)
                    exit(EXIT_FAILURE);
            }
            word[word_len] = (char)current_input;
            word[word_len + 1] = '\0';
            word_len += 1;
            
            previous_input = current_input;
            continue;
        }

        //
        if (current_input == '\n' ||  current_input == EOF) 
        {
            row_number += 1;
            if (!isWhitespace(previous_input))
            {
                if (proceedWord(row, word))
                {
                    word = (char *)malloc(word_buffer_init_size * sizeof(char));
                    word_buffer_size = word_buffer_init_size;
                    if (word == NULL)
                        exit(EXIT_FAILURE);
                }
                word_len = 0;
                word[0] = '\0';
            }

            if (row->num_elements > 0)
            {
                
                    if (insertRowTree(&row_counter, row, row_number))
                    {
                        removeAllWordTree(row->row_words);
                        free(row);
                    }
                row = (Row *)malloc(sizeof(Row));
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