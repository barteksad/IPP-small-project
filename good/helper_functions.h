#include <stdbool.h> 
#include "row.h"
// checks if x is a whitespace character
bool isWhitespace (int x);

bool proceedWord(Row *row, char *word);

bool checkIfOctalAndPossiblyAdd(char *word, Row *row);

bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row);

bool isOnlyNumeric(char *word);