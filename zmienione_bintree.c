#include <stdio.h>
#include <stdlib.h>
struct Node;

typedef struct Node* Tree;


enum DataType
{
    INTIGER,
    FLOATING_POINT,
    NOT_A_NUMBER
};

enum WordCompareResult
{
    SMALLER,
    EQUAL,
    GREATER
};


typedef struct{  
    enum DataType data_type;
    int count;
    union
    {
        long long int intiger;
        long double floating_point;
        char *not_a_number;
    };

} Word;



struct Node
{
    Word stored_word;
    Tree left, right;
};


short compareWords(Word lhs_word, Word rhs_word)
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

        if (lhs_value < rhs_value)
            return SMALLER;
        else if (lhs_value > rhs_value)
            return GREATER;
        else
            return EQUAL;
    }

}   

// Jeśli w drzewie wskazywanym przez treePtr nie występuje wartość x,
// to zostaje wstawiona.
void insert(Tree *treePtr, Word word);

// Wypisuje na wyjście wartości przechowywane w drzewie t w porządku rosnącym.
void printAll(Tree t);

// Usuwa z pamięci drzewo t.
void removeAll(Tree t);

// ----------

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
                printf("%d ", t->stored_word.intiger);
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
        free(t);
    }
}



int main()
{
    Tree t = NULL;
    Word temp;

    temp.floating_point = (long double)10.22;
    temp.data_type = FLOATING_POINT;
    insert(&t, temp);

    temp.intiger = 3;
    temp.data_type = INTIGER;
    insert(&t, temp);

    temp.not_a_number = "dsad";
    temp.data_type = NOT_A_NUMBER;
    insert(&t, temp);


    printAll(t);
    removeAll(t);
}