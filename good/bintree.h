#pragma once
#include <stdbool.h> 

struct Node;

typedef struct Node* Tree;

enum DataType
{
    FLOATING_POINT,
    NOT_A_NUMBER
};

enum WordCompareResult
{
    SMALLER,
    EQUAL,
    GREATER
};

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




enum WordCompareResult compareWords(Word lhs_word, Word rhs_word);

bool insert(Tree *treePtr, Word word);

void printAll(Tree t);

void removeAll(Tree t);

bool checkPresence(Tree t, Word word);

bool compareTrees(Tree t1, Tree t2);



