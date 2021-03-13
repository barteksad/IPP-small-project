#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"


struct Node
{
    Word stored_word;
    Tree left, right;
};


enum WordCompareResult compareWords(Word lhs_word, Word rhs_word)
{   
    // different data types
    if (lhs_word.data_type < rhs_word.data_type)
        return SMALLER;
    if (lhs_word.data_type > rhs_word.data_type)
        return GREATER;

    if (lhs_word.data_type ==  INTIGER)
    {
        long long int lhs_value = lhs_word.intiger;
        long long int rhs_value = rhs_word.intiger;

        if (lhs_value < rhs_value)
            return SMALLER;
        else if (lhs_value > rhs_value)
            return GREATER;
        else
            return EQUAL;
    }
    if (lhs_word.data_type ==  FLOATING_POINT)
    {
        long double lhs_value = lhs_word.floating_point;
        long double rhs_value = rhs_word.floating_point;

        if (lhs_value < rhs_value)
            return SMALLER;
        else if (lhs_value > rhs_value)
            return GREATER;
        else
            return EQUAL;
    }
    if (lhs_word.data_type ==  NOT_A_NUMBER)
    {
        char *lhs_value = lhs_word.not_a_number;
        char *rhs_value = rhs_word.not_a_number;

        int compare_info = strcmp(lhs_value, rhs_value);

        if (compare_info < 0)
            return SMALLER;
        else if (compare_info > 0)
            return GREATER;
        else
            return EQUAL;
    }

}   

void insert(Tree *treePtr, Word word)
{
    if (*treePtr == NULL)
    {
        Tree temp = (Tree)malloc(sizeof(struct Node));
        // memory error
        if (temp == NULL)
            exit(EXIT_FAILURE);
        temp->stored_word = word;
        temp->left = NULL;
        temp->right = NULL; 
        *treePtr = temp;
    }

    // how is left compared to right
    enum WordCompareResult compare_result = compareWords((*treePtr)->stored_word, word);

    if (compare_result == SMALLER)
        insert(&((*treePtr)->right), word);
    else if (compare_result == GREATER)
        insert(&((*treePtr)->left), word);
    else
        (*treePtr)->stored_word.count += 1;
}

void printAll(Tree t)
{
    if (t != NULL)
        {
            printAll(t->left);
            if (t->stored_word.data_type == INTIGER)
                printf("%lld ", t->stored_word.intiger);
            else if (t->stored_word.data_type == FLOATING_POINT)
                printf("%Lf ", t->stored_word.floating_point);
            else if (t->stored_word.data_type == NOT_A_NUMBER)
                printf("%s ", t->stored_word.not_a_number);
            printAll(t->right);
        }
}

void removeAll(Tree t)
{
    if(t != NULL)
    {
        removeAll(t->left);
        removeAll(t->right);
        if (t->stored_word.data_type == NOT_A_NUMBER)
            free(t->stored_word.not_a_number);
        free(t);
    }
}


bool checkPresence(Tree t, Word word)
{
    enum WordCompareResult compare_result = compareWords(t->stored_word, word);

    if (compare_result == SMALLER)
        checkPresence(t->right, word);
    else if (compare_result == GREATER)
        checkPresence(t->left, word);
    else
        return t->stored_word.count == word.count;
}

bool compareTrees(Tree t1, Tree t2)
{
    if (t1 == NULL)
        return true;

    if (checkPresence(t2, t1->stored_word))
        return compareTrees(t1->left, t2) && compareTrees(t1->right, t2);
}
