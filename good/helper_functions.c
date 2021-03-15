#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "helper_functions.h"

bool isWhitespace (int x) {
    // ' ', '\t', '\n', '\v', '\f', '\r'
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
        case 'r':
            return true;
        default:
            return false;
    }
}

/*

printf("%llu\n", strtoull(word, &endPtr,10));
printf("%d %ld %ld %ld", strlen(word), word, word + strlen(word), endPtr);


liczbę całkowitą zapisaną dziesiętnie (rozpoznawane wartości z przedziału przynajmniej od -9223372036854775808 do 18446744073709551615), np. 42, -1, 09, +2, 0, -0, +0, -02;
liczbę całkowitą nieujemną zapisaną szesnastkowo (rozpoznawane wartości przynajmniej do 18446744073709551615), np. 0X0001, 0XABC;
liczbę całkowitą nieujemną zapisaną ósemkowo (rozpoznawane wartości przynajmniej do 18446744073709551615), np. 0177, 0001;
liczbę zmiennoprzecinkową, np. 0.25, .33, -1E-1, INF, -INF.


*/

bool checkIfOctalAndPossiblyAdd(char *word, Row *row)
{
    int word_len = strlen(word);

    char *endPtr;
    long double possiblyInt = strtoull(word, &endPtr, 8);
    if (endPtr == (word + word_len))
    {
        addFloat(row, possiblyInt);
        // printf("%Lf ", possiblyInt);
        return true;
    }
    else
        return false;
}

bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row)
{
    int word_len = strlen(word);
    char *endPtr;
    long double possiblyFloat = strtold(word, &endPtr);
    if (endPtr == word + word_len)
    {
        addFloat(row, possiblyFloat);
        // printf("%Lf ", possiblyFloat);
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
    // try to convert it to a numberstr
    // in case of failure it must be not a number
    if (strcmp(word, "nan") == 0 || strcmp(word, "nan") == 0 || strcmp(word, "nan") == 0)
        return addNotANumber(row, word);


    // if it start with +/- it can be intiger/floating point or not a number
    if (word[0] == '-' || word[0] == '+')
    {
        if (!checkIfFloatingPointAndPossiblyAdd(word, row))
            return addNotANumber(row, word);
        return true;
    }
    else if (word[0] == '0')
        if (checkIfOctalAndPossiblyAdd(word, row))
            return true;
    
    if (checkIfFloatingPointAndPossiblyAdd(word, row))
        return true;
    else 
        return addNotANumber(row, word);
}