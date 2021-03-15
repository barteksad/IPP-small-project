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
    int current_input, previous_input = ' ';
    unsigned int row_number = 0;
    RowTree row_counter = NULL;
    char * word = (char *)malloc(1);
    word[0] = '\0';

    Row *row = (Row *)malloc(sizeof(Row));
    printf("\n init row ptr: %lld\n", row);

    row->num_elements = 0;
    row->num_unique_elements = 0;
    row->row_words = NULL;

    while(true) 
    {
        current_input = getc(stdin);
        // check if comment or invalid row :
        // either contains '#' or ascii character not in range [33, 126]
        if ((current_input == '#' || current_input < 33 || current_input > 126) && (!isWhitespace(current_input) && (current_input != EOF)))
        {
            row_number += 1;
            if (current_input != '#')
                fprintf(stderr, "ERROR %d\n", row_number);

            while((current_input = getc(stdin)) != EOF)
                if (current_input == '\n')
                    break;

            removeAllWordTree(row->row_words);
            row->num_elements = 0;
            row->num_unique_elements = 0;
            row->row_words = NULL;
            free(word);
            word = (char *)malloc(1);
            word[0] = '\0';
            previous_input = ' ';

            continue;
        }

        if (isWhitespace(current_input) && current_input != '\n')
        {
            // if previous character was also a whitespace nothing to do
            // if previous character wasn't a whitespace, there is new word to proceed
            if (!isWhitespace(previous_input))
            {
                if (proceedWord(row, word))
                    free(word);
                word = (char *)malloc(1);
                word[0] = '\0';                      
                previous_input = current_input;
            }

            continue;
        }
        
        if(!isWhitespace(current_input) && current_input != EOF)
        {
            size_t len = strlen(word);
            word = (char*)realloc(word, len + 1);
            if (word == NULL)
                exit(EXIT_FAILURE);
            word[len] = (char)current_input;
            word[len + 1] = '\0';
            previous_input = current_input;

            continue;
        }
        if (current_input == '\n' ||  current_input == EOF) 
        {
            row_number += 1;
            if (!isWhitespace(previous_input))
            {
                if (proceedWord(row, word))
                    free(word);
                word = (char *)malloc(1);
                word[0] = '\0'; 
            }
            
            // printf("\n\n%d\n\n", compareTreesWordTree(row->row_words, row->row_words));
            // printf("%d\n", row->num_elements);
            // printAllWordTree(row->row_words);
            printf("\nrow number : %d \n", row_number);
            if (row->num_elements > 0)
                if (insertRowTree(&row_counter, row, row_number))
                {
                    removeAllWordTree(row->row_words);
                    free(row);
                }
            row = (Row *)malloc(sizeof(Row));
            row->num_elements = 0;
            row->num_unique_elements = 0;

            row->row_words = NULL;
            previous_input = ' ';

            if (current_input == EOF)
                break;
        }
    }
    printRows(row_counter);
    free(word);
    free(row);


    removeAllRowTree(row_counter);

    // free(row_counter);

    exit(EXIT_SUCCESS);
}