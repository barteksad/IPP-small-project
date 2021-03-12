#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "helper_functions.h"



int main() {
    int current_input, previous_input = ' ';
    unsigned int row_number = 0;
    char *word = "";

    while((current_input = getc(stdin)) != EOF) 
    {
        // check if comment or invalid row :
        // either contains '#' or ascii character not in range [33, 126]
        if ((current_input == '#' || current_input < 33 || current_input > 126) && (!isWhitespace(current_input)))
        {
            row_number += 1;
            printf("Invalid row! %d, %c", current_input, (char)current_input);
            while((current_input = getc(stdin)) != EOF)
                if (current_input == '\n')
                    break;
        }   

        if (isWhitespace(current_input))
        {
            // if previous character was also a whitespace nothing to do
            // if previous character wasn't a whitespace, there is new word to proceed
            if (!isWhitespace(previous_input))
            /*
            # TODO
            ****
            */
            previous_input = current_input;
            free(word);
            word = "";
        }
        else
        {
            // extend word size and store append current char at the end
            size_t len = strlen(word);
            char *temp1 = malloc(len + 1 + 1);
            char *temp2 = word;
            strcpy(temp1, word);
            temp1[len] = (char)current_input;
            temp1[len + 1] = '\0';
            word = temp1;
            printf("%s ", word);
            free(temp2);
        }



        if (current_input == '\n') 
        {
            row_number += 1;
            if (!isWhitespace(previous_input))
                proceedWord(word);

            
            // printf("\nrow number : %d \n", row_number);
        }
    }

    free(word);
}