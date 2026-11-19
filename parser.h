#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast_simple.h"

typedef struct {
    Lexer* lexer;
    Token currentToken; // Текущий токен
    Token peekToken;    // Следующий токен (для заглядывания вперед)
} Parser;

Parser* NewParser(Lexer* l);
void FreeParser(Parser* p);
Node* ParseExpression(Parser* p);

#endif