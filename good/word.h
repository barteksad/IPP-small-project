#pragma once
#include <stdbool.h> 

struct WordNode;

typedef struct WordNode* WordTree;

// needed to store info which datatype is in a word
enum DataType
{
    FLOATING_POINT,
    NOT_A_NUMBER
};

// for comparing words
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

// number < not a number
// otherwise normal comparison
// when inserting words doesn't comapre word count
// check_count=true if called by compareTreesWordTree
enum CompareResult compareWords(Word lhs_word, Word rhs_word, bool check_count);

// return true if added word was new
// and false if it has already been present, then just increase its count
bool insertWordTree(WordTree *treePtr, Word word, int word_len);

void printAllWordTree(WordTree t);

void removeAllWordTree(WordTree t);

// traverse tree in order and writes pointers to all tree elements to the array 
int goDFSWordTree(WordTree t, Word **words, int current_num);

// compares two word trees
// only called when they contain the same number of elements
// calls goDFSWordTree and compares next words
enum CompareResult compareTreesWordTree(WordTree t1, WordTree t2, int num_elements_in_each_tree);




