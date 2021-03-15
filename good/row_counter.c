#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "row_counter.h"

struct RowNode
{
    Row *row;
    int *row_numbers;
    int how_many_rows_similar;
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
        (*row_tree_ptr)->how_many_rows_similar = 1;
        (*row_tree_ptr)->left = NULL;
        (*row_tree_ptr)->right = NULL;

        num_rows_groups += 1;
        printf("NOT FREE\n");
        return false;
    }

    // how is left compared to right
    // printf("%lld ---------------- %lld", (*row_tree_ptr)->row->row_words, row->row_words);
    enum CompareResult compare_result = compareTwoRows(*(*row_tree_ptr)->row, *row);
    // printf("+++%d++++\n", compare_result == EQUAL);
    if (compare_result == SMALLER)
        return insertRowTree(&((*row_tree_ptr)->right), row, row_number);
    else if (compare_result == GREATER)
        return insertRowTree(&((*row_tree_ptr)->left), row, row_number);
    else
    {
        (*row_tree_ptr)->row_numbers = (int *)realloc((*row_tree_ptr)->row_numbers, sizeof(int) * ((*row_tree_ptr)->how_many_rows_similar + 1));
        if ((*row_tree_ptr)->row_numbers == NULL)
            exit(EXIT_FAILURE);
        *((*row_tree_ptr)->row_numbers + ((*row_tree_ptr)->how_many_rows_similar)) = row_number;
        // printf("+-+-%d\n", *((*row_tree_ptr)->row_numbers + ((*row_tree_ptr)->how_many_rows_similar)));
        (*row_tree_ptr)->how_many_rows_similar +=1;        
        return true;
    }
}

int goDFSRowTree(RowTree t, RowTree *rows_groups[], int current_num)
{
    if (t != NULL)
    {
        int this_num = goDFSRowTree(t->left, rows_groups, current_num);
        *(rows_groups + this_num) = t;
        return goDFSRowTree(t->right, rows_groups, this_num + 1);
    }
    else
        return current_num;
}

int compareRowGroups(const void *lhs, const void *rhs)
{
    // printf("%lld\n", *(*(RowTree *)lhs)->row_numbers);
    return (*(*(RowTree *)lhs)->row_numbers - *(*(RowTree *)rhs)->row_numbers);
}

void printRows(RowTree row_counter)
{
    // printf("---%d---", row_counter->how_many_rows_similar);

    RowTree *rows_gropus = (RowTree *)malloc(num_rows_groups * sizeof(RowTree));
    goDFSRowTree(row_counter, rows_gropus, 0);
    qsort(rows_gropus, num_rows_groups, sizeof(RowTree), compareRowGroups);
    // printf("wypisdz\n");

    for(int i = 0; i < num_rows_groups; i++)
    {
        for(int j = 0; j < rows_gropus[i]->how_many_rows_similar; j++)
        {
            // printf("\n%d  ", rows_gropus[i]->how_many_rows_similar);
            if (j != 0)
                printf(" ");
            printf("%d", *(rows_gropus[i]->row_numbers + j));
        }
        printf("\n");
    }
    free(rows_gropus);
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