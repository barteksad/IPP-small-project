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

bool checkIfOctalAndPossiblyAdd(char *word, Row *row, size_t word_len)
{
    char *endPtr;
    long double possiblyInt = (long double)strtoull(word, &endPtr, 8);
    if (endPtr == (word + word_len))
    {
        addFloat(row, possiblyInt);
        return true;
    }
    return false;
}

bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row, size_t word_len, bool read_hex_int)
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
    return false;
}

void proceedWord(Row *row, char *word, size_t word_len)
{
    // konwertuje wszystkie litery na małe
    for(int i = 0; word[i] != '\0'; i++){
        word[i] = tolower(word[i]);
    }

    // szczególne przypadki nie wyłapywane przez standardowe funkcje
    if (strcmp(word, "+nan") == 0 || strcmp(word, "-nan") == 0 || strcmp(word, "nan") == 0)
        addNotANumber(row, word, word_len);
    else if(strcmp(word, "0x") == 0)
        addFloat(row, 0L);

    // jeśli słowo zaczyna się na 0x, może być tylko intem lub nie liczbą, nie dopuszczamy iczb zmiennoprzecinkowych w zapisie szesnastkowym
    else if (word_len > 1 && word[0] == '0' && word[1] == 'x')
    {
        if (!checkIfFloatingPointAndPossiblyAdd(word, row, word_len, true))
            addNotANumber(row, word, word_len);
    }

    // jeśli zaczyna się +/- to nie może być liczbą w szesnastkową ani ósemkową
    else if (word[0] == '-' || word[0] == '+')
    {
        // czyli +0x ... to słowa
        if (word_len > 2  && word[1] == '0' && word[2] == 'x')
            addNotANumber(row, word, word_len);
        else if (!checkIfFloatingPointAndPossiblyAdd(word, row, word_len, false))
            addNotANumber(row, word, word_len);
    }
    // 0 (0x itp już rozpatrzone ) na początku, może być to liczba ósemkowa
    else if (word[0] == '0')
    {
        if(!checkIfOctalAndPossiblyAdd(word, row, word_len))
        {
            // wszystkie szczególen przypadki rozpatrzone, próbujemy wczytać jako liczbę
            // jak się nie uda, dodajemy jako nie liczbą
            if (!checkIfFloatingPointAndPossiblyAdd(word, row, word_len, false))
            addNotANumber(row, word, word_len);
        }
    }
    else
    {
        // wszystkie szczególen przypadki rozpatrzone, próbujemy wczytać jako liczbę
        // jak się nie uda, dodajemy jako nie liczbą
        if (!checkIfFloatingPointAndPossiblyAdd(word, row, word_len, false))
        addNotANumber(row, word, word_len);
    }
}
    


