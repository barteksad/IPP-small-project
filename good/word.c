#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"


struct WordNode
{
    Word stored_word;
    WordTree left, right;
};

enum CompareResult compareWords(Word lhs_word, Word rhs_word, bool check_count)
{   
    // liczba < nie liczby
    if (lhs_word.data_type < rhs_word.data_type)
        return SMALLER;
    else if (lhs_word.data_type > rhs_word.data_type)
        return BIGGER;
    
    else if (lhs_word.data_type ==  FLOATING_POINT)
    {
        long double lhs_value = lhs_word.floating_point;
        long double rhs_value = rhs_word.floating_point;

        if (lhs_value < rhs_value)
            return SMALLER;
        else if (lhs_value > rhs_value)
            return BIGGER;
        else if (check_count)
            {
                if (lhs_word.count < rhs_word.count)
                    return SMALLER;
                else if (lhs_word.count > rhs_word.count)    
                    return BIGGER;
                else    
                    return EQUAL;
            }
        else
            return EQUAL;
    }
    else
    {
        char *lhs_value = lhs_word.not_a_number;
        char *rhs_value = rhs_word.not_a_number;

        int compare_info = strcmp(lhs_value, rhs_value);

        if (compare_info < 0)
            return SMALLER;
        else if (compare_info > 0)
            return BIGGER;
        else if (check_count)
            {
                if (lhs_word.count < rhs_word.count)
                    return SMALLER;
                else if (lhs_word.count > rhs_word.count)    
                    return BIGGER;
                else    
                    return EQUAL;
            }
        else
            return EQUAL;
    }

}   


bool insertWordTree(WordTree *treePtr, Word word, int word_len)
{
    if (*treePtr == NULL)
    {
        *treePtr = (WordTree)malloc(sizeof(struct WordNode));
        if (*treePtr == NULL)
            exit(EXIT_FAILURE);
        if (word.data_type == NOT_A_NUMBER)
        {
            word.not_a_number = (char *)realloc(word.not_a_number, (strlen(word.not_a_number) + 1) * sizeof(char));
            if (word.not_a_number == NULL)
                exit(EXIT_FAILURE);
        }
        (*treePtr)->stored_word = word;
        // jeśli dodajemy nową nie liczbę to trzeba na jej napis zaalokować nową pamięć
        // ponieważ aktualna jest współdzielona z bufferem na wczytywane słowa z main()
        if (word.data_type == NOT_A_NUMBER)
        {
            char *new_memory_for_stored_string = (char *)malloc((word_len + 1) * sizeof(char));
            if (!new_memory_for_stored_string)
                exit(EXIT_FAILURE);
            strcpy(new_memory_for_stored_string, word.not_a_number);
            (*treePtr)->stored_word.not_a_number = new_memory_for_stored_string;

        }
        (*treePtr)->stored_word.count = 1;
        (*treePtr)->left = NULL;
        (*treePtr)->right = NULL;
<<<<<<< HEAD
 
        return true;
=======
        return false;
>>>>>>> try_buffer_again
    }

    enum CompareResult compare_result = compareWords((*treePtr)->stored_word, word, false);

    if (compare_result == SMALLER)
        return insertWordTree(&((*treePtr)->right), word, word_len);
    else if (compare_result == BIGGER)
        return insertWordTree(&((*treePtr)->left), word, word_len);
    else
    {
        (*treePtr)->stored_word.count += 1;
        return false;
    }
}

void printAllWordTree(WordTree t)
{
    if (t != NULL)
        {
            printAllWordTree(t->left);
            if (t->stored_word.data_type == FLOATING_POINT)
                printf("%Lf ", t->stored_word.floating_point);
            else if (t->stored_word.data_type == NOT_A_NUMBER)
                printf("%s ", t->stored_word.not_a_number);
            printAllWordTree(t->right);
        }
}

void removeAllWordTree(WordTree t)
{
    if(t != NULL)
    {
        removeAllWordTree(t->left);
        removeAllWordTree(t->right);
        if (t->stored_word.data_type == NOT_A_NUMBER)
            free(t->stored_word.not_a_number);

        free(t);
    }
}

// zwykłe przejście in order
// current_num jest porzebne żemy każdy element wpisać w odpowiednie miejscie, zgodne z kolejnością in order
int goDFSWordTree(WordTree t, Word **words, int current_num)
{
    if (t != NULL)
    {
        int this_num = goDFSWordTree(t->left, words, current_num);
        *(words + this_num) = &t->stored_word;
        return goDFSWordTree(t->right, words, this_num + 1);
    }
    else
        return current_num;
}

enum CompareResult compareTreesWordTree(WordTree t1, WordTree t2, int num_elements_in_each_tree)
{
    Word **t1_words = malloc(num_elements_in_each_tree * sizeof(Word*));
    if (!t1_words)
        exit(EXIT_FAILURE);
    Word **t2_words = malloc(num_elements_in_each_tree * sizeof(Word*));
    if (!t2_words)
        exit(EXIT_FAILURE);

    goDFSWordTree(t1, t1_words, 0);
    goDFSWordTree(t2, t2_words, 0);

    for(int i = 0; i < num_elements_in_each_tree; i++)
    {
        enum CompareResult word_compare_result = compareWords(*t1_words[i], *t2_words[i], true);
        if (word_compare_result == EQUAL)
            continue;
        else
        {
            free(t1_words);
            free(t2_words);
            return word_compare_result;
        }
    }
    free(t1_words);
    free(t2_words);
    return EQUAL;
}
