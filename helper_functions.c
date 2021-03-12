#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "helper_functions.h"

bool isWhitespace (int x) {
    // ' ', '\t', '\n', '\v', '\f', '\r'
    switch (x) {
        case ' ':
            return true;
        case '\t':
            return true;
        case '\n':
            return true;
        case '\v':
            return true;
        case '\f':
            return true;
        case 'r':
            return true;
        default:
            return false;
    }
}

/*

printf("%llu\n", strtoull(word, &endPtr,10));
printf("%d %ld %ld %ld", strlen(word), word, word + strlen(word), endPtr);


liczbę całkowitą zapisaną dziesiętnie (rozpoznawane wartości z przedziału przynajmniej od -9223372036854775808 do 18446744073709551615), np. 42, -1, 09, +2, 0, -0, +0, -02;
liczbę całkowitą nieujemną zapisaną szesnastkowo (rozpoznawane wartości przynajmniej do 18446744073709551615), np. 0X0001, 0XABC;
liczbę całkowitą nieujemną zapisaną ósemkowo (rozpoznawane wartości przynajmniej do 18446744073709551615), np. 0177, 0001;
liczbę zmiennoprzecinkową, np. 0.25, .33, -1E-1, INF, -INF.


*/

void proceedWord(char *word)
{
    // convert string to lowercase
    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
    size_t word_len = len(word);

    // try to convert it to a numberstr
    // in case of failure it must be not a number

    // if it start with +/- it can be only intiger or floating point
    if (word[0] == '-' || word[0] == '+')
    {
        char *endPtr;
        float possiblyFloat = strtof(word, &endPtr);
        if (possiblyFloat == strtof("nan"))
            // proceed not a number
        if (endPtr == (word + word_len))
        {

        }
    }
}