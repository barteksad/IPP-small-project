#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"


struct WordNode
{
    Word stored_word;
    WordTree left, right;
};


enum CompareResult compareWords(Word lhs_word, Word rhs_word)
{   
    // different data types
    if (lhs_word.data_type < rhs_word.data_type)
        return SMALLER;
    else if (lhs_word.data_type > rhs_word.data_type)
        return GREATER;

    else if (lhs_word.data_type ==  FLOATING_POINT)
    {
        long double lhs_value = lhs_word.floating_point;
        long double rhs_value = rhs_word.floating_point;

        if (lhs_value < rhs_value)
            return SMALLER;
        else if (lhs_value > rhs_value)
            return GREATER;
        else
            {
                if (lhs_word.count < rhs_word.count)
                    return SMALLER;
                else if (lhs_word.count > rhs_word.count)    
                    return GREATER;
                else    
                    return EQUAL;
            }
    }
    else
    // else (lhs_word.data_type ==  NOT_A_NUMBER)
    {
        char *lhs_value = lhs_word.not_a_number;
        char *rhs_value = rhs_word.not_a_number;

        int compare_info = strcmp(lhs_value, rhs_value);

        if (compare_info < 0)
            return SMALLER;
        else if (compare_info > 0)
            return GREATER;
        else
            {
                if (lhs_word.count < rhs_word.count)
                    return SMALLER;
                else if (lhs_word.count > rhs_word.count)    
                    return GREATER;
                else    
                    return EQUAL;
            }
    }

}   

bool insertWordTree(WordTree *treePtr, Word word)
{
    if (*treePtr == NULL)
    {
        *treePtr = (WordTree)malloc(sizeof(struct WordNode));
        // memory error
        if (*treePtr == NULL)
            exit(EXIT_FAILURE);
        (*treePtr)->stored_word = word;
        (*treePtr)->stored_word.count = 1;
        (*treePtr)->left = NULL;
        (*treePtr)->right = NULL;
        // printf("%Lf ", word.floating_point);
 
        return false;
    }

    // how is left compared to right
    enum CompareResult compare_result = compareWords((*treePtr)->stored_word, word);

    if (compare_result == SMALLER)
        return insertWordTree(&((*treePtr)->right), word);
    else if (compare_result == GREATER)
        return insertWordTree(&((*treePtr)->left), word);
    else
    {
        (*treePtr)->stored_word.count += 1;
        return true;
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


int goDFSWordTree(WordTree t, Word *words[], int current_num)
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
    Word **t2_words = malloc(num_elements_in_each_tree * sizeof(Word*));

    goDFSWordTree(t1, t1_words, 0);
    goDFSWordTree(t2, t2_words, 0);

    for(int i = 0; i < num_elements_in_each_tree; i++)
    {
        // printf("---%s %s\n", t1_words[i], t2_words[i]);
        enum CompareResult word_compare_result = compareWords(*t1_words[i], *t2_words[i]);
        printf("%Lf %Lf %d\n", t1_words[i]->floating_point, t2_words[i]->floating_point, word_compare_result);
        printf("%d\n", t1_words[i]->floating_point == t2_words[i]->floating_point);

        if (word_compare_result == EQUAL)
            continue;
        else
        {
            free(t1_words);
            free(t2_words);
            return word_compare_result;
        }
    }
    printf("EQUAL\n");
    return EQUAL;
}
