#include <stdio.h>
#include <stdlib.h>
struct Node;

typedef struct Node* Tree;

struct Node
{
    int value;
    Tree left, right;
};

// Jeśli w drzewie wskazywanym przez treePtr nie występuje wartość x,
// to zostaje wstawiona.
void insert(Tree *treePtr, int x);

// Wypisuje na wyjście wartości przechowywane w drzewie t w porządku rosnącym.
void printAll(Tree t);

// Usuwa z pamięci drzewo t.
void removeAll(Tree t);

// Usuwa z niepustego drzewa wskazywanego przez treePtr najmniejszą wartość
// i zwraca ją jako wynik.
int removeMin(Tree *treePtr);

// Jeśli w drzewie wskazywanym przez treePtr znajduje się wartość x, usuwa ją.
void removeValue(Tree *treePtr, int x);


// ----------

void insert(Tree *treePtr, int x)
{
    if (*treePtr == NULL)
    {
        Tree temp = (Tree)malloc(sizeof(struct Node));
        // memory error
        if (temp == NULL)
            exit(EXIT_FAILURE);
        temp->value = x;
        temp->left = NULL;
        temp->right = NULL; 
        *treePtr = temp;
    }
    else if ((*treePtr)->value < x)
        insert(&((*treePtr)->right), x);
    else if ((*treePtr)->value > x)
        insert(&((*treePtr)->left), x);
}

void printAll(Tree t)
{
    if (t != NULL)
        {
            printAll(t->left);
            printf("%d ", t->value);
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

int removeMin(Tree *treePtr)
{
    if ((*treePtr)->left == NULL)
        {
            int min_val = (*treePtr)->value;
            Tree *temp = &(*treePtr)->right;
            free(*treePtr);
            *treePtr = *temp;
            return min_val;
        }
    else
        removeMin(&(*treePtr)->left);
}

void removeValue(Tree *treePtr, int x)
{
    if((*treePtr) != NULL)
    {
        if ((*treePtr)->value < x)
            removeValue(&(*treePtr)->right, x);
        else if ((*treePtr)->value > x)
            removeValue(&(*treePtr)->left, x);
        else
        {
            if ((*treePtr)->right == NULL)
                *treePtr = (*treePtr)->left;
            else
                (*treePtr)->value = removeMin(&(*treePtr)->right);
        }
    }
        
}



int main()
{
    Tree t = NULL;
    int wartosc;

    while((scanf("%d", &wartosc) == 1))
    {
        insert(&t, wartosc);
    }
    printf("%d\n\n", removeMin(&t));

    removeValue(&t, 32);

    removeValue(&t, 1);

    removeValue(&t, 766);

    removeValue(&t, 543);

    printAll(t);
    removeAll(t);
}