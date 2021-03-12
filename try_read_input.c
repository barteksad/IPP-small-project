#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <math.h>
bool isWhitespace (char x) {
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

enum d {
    k =1,
    j=3
};

/*

18446744073709551615
1844674407370955161500000e-5
1844674407370955161500000.00e-5
*/

void main() {
    // char input[1000];
    char *ptr;
    char *word = "18446744073709551615.000  ";
    printf("%llu\n", strtoull(word, &ptr, 10));
    printf("%ld %ld %ld", word,  strlen(word), ptr);

}

/*

    char *str = "blablabla";
    char c = 'H';

    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); 
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

    printf( "%s\n", str2 );

    free( str2 ); 
    
*/