#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "helper_functions.h"
#include "row.h"
#include "row_counter.h"

// rozmiar 1024 brzmi rozsądnie jako maksymalna długość wszytywanego słowa
// dynamicznie zwiększany jeśli zajdzie potrzeba
#define INITIAL_WORD_BUFFER_SIZE 1024

int main() 
{
    int current_input, previous_input = '\n';
    unsigned int row_number = 0;
    // BST do przechowywania kolejnych wierszy
    RowTree row_counter = NULL;

    size_t current_word_buffer_size = INITIAL_WORD_BUFFER_SIZE;
    // buffer na kolejne prawidłowe znaki z wejścia, 
    char * word = (char *)malloc(current_word_buffer_size * sizeof(char));
    if (!word)
        exit(EXIT_FAILURE);
    // długość aktualnie wczytywanego poprawnego słowa
    size_t word_len = 0;

    // BTS do przechowywania słów z jednego wiersza
    Row *row = (Row *)malloc(sizeof(Row));
    if (!row)
        exit(EXIT_FAILURE);
    row->num_elements = 0;
    row->num_unique_elements = 0;
    row->row_words = NULL;

    while(true) 
    {
        current_input = getc(stdin);
        
        // sprawdzenie warunków, czy aktualny wiersz jest poprawny / nie jest komentarzem
        if ((
            (current_input == '#' && previous_input == '\n') || 
            current_input < 33 || current_input > 126) && (!isWhitespace(current_input) && (current_input != EOF)))
        {
            row_number += 1;
            if (current_input != '#')
                fprintf(stderr, "ERROR %d\n", row_number);

            // jeśli nie należy przetwarzać tego wiersza, pomijamy wszystko do znaku nowej lini
            while((current_input = getc(stdin)) != EOF)
                if (current_input == '\n')
                    break;

            // trzema usunąć wszystkie wczytane słowa z tego wiersza
            removeAllWordTree(row->row_words);
            row->row_words = NULL;
            row->num_elements = 0;
            row->num_unique_elements = 0;
            word_len = 0;
            previous_input = '\n';
            continue;
        }

        if (isWhitespace(current_input) || current_input == EOF)
        {
            // jeśli poprzedni input nie był białym znakiem to znaczy, że właśnie skończyliśmy wczytywać słowo i trzeba je dodać
            if (!isWhitespace(previous_input))
            {
                word[word_len] = '\0';
                proceedWord(row, word, word_len);
                word_len = 0;              
            }
            previous_input = current_input;
        }
        
        // jeśli aktualny input jest poprawnym, nie białym znakiem dopisujemy go do buffera na słowo i ew zwiększamy rozmiar buffera
        if(!isWhitespace(current_input) && current_input != EOF)
        {
            if (word_len > current_word_buffer_size - 1)
            {
                word = (char *)realloc(word, current_word_buffer_size * 2 * sizeof(char));
                if (!word)
                    exit(EXIT_FAILURE);
                current_word_buffer_size *= 2;
            }
            word[word_len] = (char)current_input;
            word_len += 1;
            previous_input = current_input;
            continue;
        }

        // koniec wiersza / koniec pliku, dodajemy aktualny wiersz do BST przechowywującego wszystkie wiersze
        if (current_input == '\n' ||  current_input == EOF) 
        {
            row_number += 1;
            if (row->num_elements > 0)
            {
                // jeśli insertRowTree zwróci false to znaczy że dodaliśmy nowy element i wskaźnik na niego wskazuje na wciąż używaną pamieć,
                // trzeba na nowy wiersz zaalokować nową
                // jeśli taki wiersz już istniał to tylko zwiększyliśmy jego liczbę, a aktualny wskaźnik można użyć ponownie po uprzednik wyzerowaniu wszytskich wartości
                if (insertRowTree(&row_counter, row, row_number))
                    removeAllWordTree(row->row_words);
                else
                {
                    row = (Row *)malloc(sizeof(Row));
                    if (!row)
                        exit(EXIT_FAILURE);
                }
                row->num_elements = 0;
                row->num_unique_elements = 0;
                row->row_words = NULL;
            }
            previous_input = '\n';
            if (current_input == EOF)
                    break;
        }
    }
    // wypisanie wszystkich wierszy w dobrej kolejności
    printRows(row_counter);
    removeAllRowTree(row_counter);
    free(word);
    free(row);
    exit(EXIT_SUCCESS);
}