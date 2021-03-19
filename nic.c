#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char *end;
    char *word = "0xfff-2e";
    printf("%Lf ",  strtold(word, &end));
    printf("\n %ld %ld %ld",word, end, strlen(word));
}