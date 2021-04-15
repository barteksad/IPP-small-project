#pragma once
#include <stdbool.h> 
#include "row.h"

bool isWhitespace (int x);

// sprawdza czy dane słowo to liczba czy nie liczba i dodaje je do aktualnego wiersza
void proceedWord(Row *row, char *word, size_t word_len);

// próbuje przeczytać dane słowo jako liczbe ósemkową i jeśli się uda, dodaje do wiersza
// zwraca true / false czy się udało
bool checkIfOctalAndPossiblyAdd(char *word, Row *row, size_t word_len);

// próbuje przeczytać dane słowo jako liczbę szesnastkową lub zmienno przecinkową i jeśli się uda, dodaje do wiersza
// zwraca true / false czy się udało
bool checkIfFloatingPointAndPossiblyAdd(char *word, Row *row, size_t word_len, bool read_hex_int);
