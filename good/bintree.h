#pragma once
#include <stdbool.h> 

struct WordNode;

typedef struct WordNode* WordTree;

enum DataType
{
    FLOATING_POINT,
    NOT_A_NUMBER
};

enum CompareResult
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




enum CompareResult compareWords(Word lhs_word, Word rhs_word);

bool insertWordTree(WordTree *treePtr, Word word);

void printAllWordTree(WordTree t);

void removeAllWordTree(WordTree t);

int goDFSWordTree(WordTree t, Word *words[], int current_num);

enum CompareResult compareTreesWordTree(WordTree t1, WordTree t2);




