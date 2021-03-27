#include <stdlib.h>
#include <stdio.h>
#include "row_counter.h"

// węzeł drzewa na wiersze
// przechowuje :
// - reprezentanta
// - numery podobnych wierszy posortowane rosnąca
// - ich liczbę
struct RowNode
{
    Row *row;
    int *row_numbers;
    int how_many_rows_similar;
    RowTree left, right;
};

// liczba unikatowych wierszy
static int num_rows_groups = 0;

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
        if(!(*row_tree_ptr)->row_numbers)
            exit(EXIT_FAILURE);
        *((*row_tree_ptr)->row_numbers) = row_number;
        (*row_tree_ptr)->how_many_rows_similar = 1;
        (*row_tree_ptr)->left = NULL;
        (*row_tree_ptr)->right = NULL;

        num_rows_groups += 1;
        return false;
    }

    // how is left compared to right
    enum CompareResult compare_result = compareTwoRows(*(*row_tree_ptr)->row, *row);
    if (compare_result == SMALLER)
        return insertRowTree(&((*row_tree_ptr)->right), row, row_number);
    else if (compare_result == BIGGER)
        return insertRowTree(&((*row_tree_ptr)->left), row, row_number);
    else
    {
        (*row_tree_ptr)->row_numbers = (int *)realloc((*row_tree_ptr)->row_numbers, sizeof(int) * ((*row_tree_ptr)->how_many_rows_similar + 1));
        if (!(*row_tree_ptr)->row_numbers)
            exit(EXIT_FAILURE);
        *((*row_tree_ptr)->row_numbers + ((*row_tree_ptr)->how_many_rows_similar)) = row_number;
        (*row_tree_ptr)->how_many_rows_similar +=1;        
        return true;
    }
}

// zwykłe przejście in order
// current_num jest porzebne żemy każdy element wpisać w odpowiednie miejscie, zgodne z kolejnością in order
int goDFSRowTree(RowTree t, RowTree *rows_groups, int current_num)
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

// nr pierwszego wiersza w lewym - nr pierwszego wiersza w prawy
int compareRowGroups(const void *lhs, const void *rhs)
{
    return (*(*(RowTree *)lhs)->row_numbers - *(*(RowTree *)rhs)->row_numbers);
}

// zapisujemy podobne wiersze do tablicy
// sortujemy je zgodnie ze specyfikacją predykatem compareRowGroups
void printRows(RowTree row_counter)
{
    RowTree *rows_gropus = (RowTree *)malloc(num_rows_groups * sizeof(RowTree));
    if (!rows_gropus)
        exit(EXIT_FAILURE);
    goDFSRowTree(row_counter, rows_gropus, 0);
    qsort(rows_gropus, num_rows_groups, sizeof(RowTree), compareRowGroups);

    for(int i = 0; i < num_rows_groups; i++)
    {
        for(int j = 0; j < rows_gropus[i]->how_many_rows_similar; j++)
        {
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