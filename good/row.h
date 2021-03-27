#pragma once
#include <stdbool.h>
#include "word.h"

// obiekt do trzymania wierszy
// składa się z BST na słowa, łącznej liczby słów oraz liczby unikatowych słów
typedef struct Row
{
    WordTree row_words;
    unsigned int num_elements;
    unsigned int num_unique_elements;
} Row;

// dodaje słowo do BST
void addWord(Row *row, Word word, int word_len);

// tworzy obiekt Word przechowójące liczbę i wywołuje addWord
void addFloat(Row *row, long double floating_point);

// tworzy obiekt Word przechowójące nie liczbę i wywołuje addWord
void addNotANumber(Row *row, char *not_a_number, int word_len);

// porównuje dwa wiersze
// zwraca info, jak się ma lewy do prawego 
enum CompareResult compareTwoRows(Row row1, Row row2);

