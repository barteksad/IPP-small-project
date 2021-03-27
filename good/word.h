#pragma once
#include <stdbool.h> 

// węzeł w drzewie przechowywującym słowa
struct WordNode;

typedef struct WordNode* WordTree;

// enum informujący, jaki typ danych jest w danym węźle
enum DataType
{
    FLOATING_POINT,
    NOT_A_NUMBER
};

// do porównywania słów/wierszy, żeby było czytelniej zamiast zwracania liczby ujemnej/0/dodatniej
enum CompareResult
{
    SMALLER,
    EQUAL,
    BIGGER
};


// typ do przechowywania słów
// zawiera:
// - info o typie słowa (liczba / nie liczba)
// - liczbę / nie liczbę
// - liczbę wystąpień danego słowa w wierszy
typedef struct Word
{  
    enum DataType data_type;
    int count;
    union
    {
        long double floating_point;
        char *not_a_number;
    };

} Word;

// porównuje dwa słowa
// liczba < nie liczby
// ten sam typ : domyślne porównanie
// jeśli wywoływana przez funkcjie porównywujące wiersze, uwzględnia też liczbę wystąpieł (check_count)
enum CompareResult compareWords(Word lhs_word, Word rhs_word, bool check_count);

// dodaje do BST
// true - element już był, zwiększamy liczbę wystąpień
// false - dodane nowy element
bool insertWordTree(WordTree *treePtr, Word word, int word_len);

void printAllWordTree(WordTree t);

void removeAllWordTree(WordTree t);

// przechodzi drzewo in order i zapisuje wskałniki do słów w danej tablicy
int goDFSWordTree(WordTree t, Word **words, int current_num);

// porównuje dwa drzewa słów
// wywoływana tylko gdy ogólna liczba słów oraz licz unikatowych słów są takie same
// goDFSWordTree zapisuje kolejne słowa in order i potem po koleji porównuje następne
// zwraca jak się ma lewe do prawego 
enum CompareResult compareTreesWordTree(WordTree t1, WordTree t2, int num_elements_in_each_tree);




