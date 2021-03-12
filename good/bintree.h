struct Node;

typedef struct Node* Tree;

typedef struct Word;

enum WordCompareResult;



short compareWords(Word lhs_word, Word rhs_word);

void insert(Tree *treePtr, Word word);

void printAll(Tree t);

void removeAll(Tree t);

void insert(Tree *treePtr, Word word)

