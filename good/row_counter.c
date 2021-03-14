#pragma once
#include <stdlib.h>
#include "row_counter.h"

struct RowNode
{
    Row *row;
    int *row_numbers;
    int how_many_rows;
    RowTree left, right;
};

bool insertRowTree(RowTree *row_tree_ptr, Row *row, int row_number)
{

    if (*row_tree_ptr == NULL)
    {

        *row_tree_ptr = (RowTree)malloc(sizeof(struct RowNode));
        // memory error
        if (*row_tree_ptr == NULL)
            exit(EXIT_FAILURE);
        (*row_tree_ptr)->row = row;
        (*row_tree_ptr)->row_numbers = (int *)malloc(sizeof(int));
        *((*row_tree_ptr)->row_numbers) = row_number;
        (*row_tree_ptr)->how_many_rows = 1;
        (*row_tree_ptr)->left = NULL;
        (*row_tree_ptr)->right = NULL;
        return false;
    }

    // how is left compared to right
    enum CompareResult compare_result = compareTreesWordTree((*row_tree_ptr)->row->row_words, row->row_words);
    
    if (compare_result == SMALLER)
        return insertRowTree(&((*row_tree_ptr)->right), row, row_number);
    else if (compare_result == GREATER)
        return insertRowTree(&((*row_tree_ptr)->left), row, row_number);
    else
    {
        (*row_tree_ptr)->row_numbers = (int *)realloc((*row_tree_ptr)->row_numbers, sizeof(int) * ((*row_tree_ptr)->how_many_rows + 1));
        if ((*row_tree_ptr)->row_numbers == NULL)
            exit(EXIT_FAILURE);
        *((*row_tree_ptr)->row_numbers + (*row_tree_ptr)->how_many_rows) = row_number;
        (*row_tree_ptr)->how_many_rows +=1;        
        return true;
    }
}

void removeAllRowTree(RowTree t)
{
    if(t != NULL)
    {
        removeAllRowTree(t->left);
        removeAllRowTree(t->right);
        removeAllWordTree(t->row->row_words);
        free(t->row);
        free(t->row_numbers);
        free(t);
    }
}