#include <stdbool.h> 
#include "row.h"
// checks if x is a whitespace character
bool isWhitespace (int x);

void proceedWord(Row *row, char *word);

bool checkIfIntAndPossiblyAdd(char *word, Row *row, int base, int word_len);

bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row, int word_len);