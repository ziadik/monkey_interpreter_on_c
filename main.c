#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
    char* input = "let five = 5;";
    Lexer* l = New(input);
    
    Token tok;
    do {
        tok = NextToken(l);
        printf("Type: %d, Literal: '%s'\n", tok.type, tok.literal);
        FreeToken(&tok); // Не забываем освобождать память!
    } while (tok.type != TOK_EOF);
    
    free(l); // Освобождаем сам лексер
    return 0;
}