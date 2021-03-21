#pragma once
#include <stdbool.h> 
#include "row.h"

bool isWhitespace (int x);

// checks if word is a number or not a number and adds it to the row
// it returns true is added word is new and it is not a number
// because then it's char* can't be modified
// if we add float, the data at char* word is no longer needed
bool proceedWord(Row *row, char *word);

bool checkIfOctalAndPossiblyAdd(char *word, Row *row, int word_len);

bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row, int word_len, bool read_hex_int);
