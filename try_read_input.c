#include <stdio.h>
#include <stdbool.h> 

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

void main() {
    char input[1000];

    while(fgets(input, sizeof input, stdin) != NULL) {
        for(int i = 0; i < 1000; i++) {
            if (input[i] == '\n') break;
            // printf("%c : %d", input[i], input[i]);
            if(!isWhitespace(input[i]))
                putchar(input[i]);
        }
    }
}