#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "helper_functions.h"

bool isWhitespace (int x) {
    switch (x) {
        case ' ':
            return true;
        case '\t':
            return true;
        case '\n':
            return true;
        case '\v':
            return true;
        case '\f':
            return true;
        case '\r':
            return true;
        default:
            return false;
    }
}

bool checkIfOctalAndPossiblyAdd(char *word, Row *row, int word_len)
{
    char *endPtr;
    long double possiblyInt = (long double)strtoull(word, &endPtr, 8);
    if (endPtr == (word + word_len))
    {
        addFloat(row, possiblyInt);
        return true;
    }
    else
        return false;
}

bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row, int word_len, bool read_hex_int)
{
    char *endPtr;
    long double possiblyFloat;
    if (read_hex_int)
        possiblyFloat = (long double)strtoull(word, &endPtr, 16);
    else
        possiblyFloat = strtold(word, &endPtr);
    if (endPtr == word + word_len)
    {
        addFloat(row, possiblyFloat);
        return true;
    }
    else
        return false;
}

bool proceedWord(Row *row, char *word)
{
    // convert string to lowercase
    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }

    // special cases
    if (strcmp(word, "+nan") == 0 || strcmp(word, "-nan") == 0 || strcmp(word, "nan") == 0)
        return addNotANumber(row, word);
    if (strcmp(word, "0x") == 0)
    {
        addFloat(row, 0L);
        return true;
    }

    int word_len = strlen(word);

    // hex numbers must be treated as intigers
    if (word_len > 1 && word[0] == '0' && word[1] == 'x')
    {
        if (!checkIfFloatingPointAndPossiblyAdd(word, row, word_len, true))
            return addNotANumber(row, word);
        else
            return false;
    }

    // if it start with +/- it can't be float or octal
    if (word[0] == '-' || word[0] == '+')
    {
        // so -0x +0x (...) is not a number
        if (word_len > 2  && word[1] == '0' && word[2] == 'x')
            return addNotANumber(row, word);
        else if (!checkIfFloatingPointAndPossiblyAdd(word, row, word_len, false))
            return addNotANumber(row, word);
        return true;
    }

    // with 0 at the beginning it can be a octal number
    else if (word[0] == '0')
        if (checkIfOctalAndPossiblyAdd(word, row, word_len))
            return true;
    
    // else try to read as a number if fails must be a word
    if (checkIfFloatingPointAndPossiblyAdd(word, row, word_len, false))
        return true;
    else 
        return addNotANumber(row, word);
}