#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "helper_functions.h"
#include "row.h"



int main() {
    int current_input, previous_input = ' ';
    unsigned int row_number = 0;

    char * word = (char *)malloc(1);
    word[0] = '\0';
    Row *row = (Row*)malloc(sizeof(Row));
    row->num_elements = 0;
    row->row_words = NULL;

    while((current_input = getc(stdin)) != EOF) 
    {
        // printf("\n'%c'-current input, '%c'-prev input\n", (char)current_input,(char)previous_input);

        // check if comment or invalid row :
        // either contains '#' or ascii character not in range [33, 126]
        if ((current_input == '#' || current_input < 33 || current_input > 126) && (!isWhitespace(current_input)))
        {
            row_number += 1;
            printf("Invalid row! %d, %c", current_input, (char)current_input);
            while((current_input = getc(stdin)) != EOF)
                if (current_input == '\n')
                    break;

            removeAll(row->row_words);
            row->num_elements = 0;
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
                proceedWord(row, word);
                previous_input = current_input;
                free(word);
                word = (char *)malloc(1);
                word[0] = '\0';
            }

            continue;
        }
        
        if(!isWhitespace(current_input))
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
        if (current_input == '\n') 
        {
            row_number += 1;
            if (!isWhitespace(previous_input))
            {
                proceedWord(row, word);       
            }
            /*
            TODO process all row
            */
            printf("\nrow number : %d \n", row_number);
            printf("%d\n", row->num_elements);
            printAll(row->row_words);
            removeAll(row->row_words);
            free(word);
            word = (char *)malloc(1);
            word[0] = '\0';
            free(row);
            row = (Row*)malloc(sizeof(Row));
            row->num_elements = 0;
            row->row_words = NULL;
            previous_input = ' ';
        }
    }
    
    free(word);
    free(row);
}