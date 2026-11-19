#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    const char* input;
    int position;     // текущая позиция в input
    int readPosition; // следующая позиция для чтения
    char ch;          // текущий символ
} Lexer;

Lexer* New(const char* input);
Token NextToken(Lexer* l);
void FreeLexer(Lexer* l); // Если будем выделять сам лексер в куче
void FreeToken(Token* t); // Важно! Освобождает память literal

#endif