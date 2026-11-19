#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // для isalpha, isdigit

// Вспомогательная функция для чтения следующего символа
static void readChar(Lexer* l) {
    if (l->readPosition >= strlen(l->input)) {
        l->ch = 0; // NUL byte, конец файла
    } else {
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition += 1;
}

Lexer* New(const char* input) {
    Lexer* l = (Lexer*)malloc(sizeof(Lexer));
    if (!l) return NULL;
    
    l->input = input;
    l->position = 0;
    l->readPosition = 0;
    l->ch = 0;
    
    readChar(l); // Инициализируем первый символ
    return l;
}

static void skipWhitespace(Lexer* l) {
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        readChar(l);
    }
}

static char* readIdentifier(Lexer* l) {
    int start = l->position;
    while (isalpha(l->ch) || l->ch == '_') {
        readChar(l);
    }
    // Выделяем память под подстроку и копируем её
    int len = l->position - start;
    char* str = (char*)malloc(len + 1);
    if (!str) return NULL;
    
    strncpy(str, &l->input[start], len);
    str[len] = '\0';
    return str;
}

static char* readNumber(Lexer* l) {
    int start = l->position;
    while (isdigit(l->ch)) {
        readChar(l);
    }
    int len = l->position - start;
    char* str = (char*)malloc(len + 1);
    if (!str) return NULL;
    
    strncpy(str, &l->input[start], len);
    str[len] = '\0';
    return str;
}

static Token newToken(TokenType type, const char* literal) {
    Token tok;
    tok.type = type;
    // Копируем строку в кучу
    if (literal) {
        tok.literal = strdup(literal); 
    } else {
        tok.literal = strdup("");
    }
    return tok;
}

// Функция для освобождения памяти токена
void FreeToken(Token* t) {
    if (t && t->literal) {
        free(t->literal);
        t->literal = NULL;
    }
}

Token NextToken(Lexer* l) {
    Token tok;
    
    skipWhitespace(l);

    switch (l->ch) {
        case '=':
            if (l->input[l->readPosition] == '=') {
                char ch = l->ch;
                readChar(l);
                tok = newToken(TOK_EQ, "==");
            } else {
                tok = newToken(TOK_ASSIGN, "=");
            }
            break;
        case '+':
            tok = newToken(TOK_PLUS, "+");
            break;
        case '-':
            tok = newToken(TOK_MINUS, "-");
            break;
        case '!':
            if (l->input[l->readPosition] == '=') {
                char ch = l->ch;
                readChar(l);
                tok = newToken(TOK_NOT_EQ, "!=");
            } else {
                tok = newToken(TOK_BANG, "!");
            }
            break;
        case '/':
            tok = newToken(TOK_SLASH, "/");
            break;
        case '*':
            tok = newToken(TOK_ASTERISK, "*");
            break;
        case '<':
            tok = newToken(TOK_LT, "<");
            break;
        case '>':
            tok = newToken(TOK_GT, ">");
            break;
        case ';':
            tok = newToken(TOK_SEMICOLON, ";");
            break;
        case ',':
            tok = newToken(TOK_COMMA, ",");
            break;
        case '(':
            tok = newToken(TOK_LPAREN, "(");
            break;
        case ')':
            tok = newToken(TOK_RPAREN, ")");
            break;
        case '{':
            tok = newToken(TOK_LBRACE, "{");
            break;
        case '}':
            tok = newToken(TOK_RBRACE, "}");
            break;
        case 0:
            tok.type = TOK_EOF;
            tok.literal = strdup("");
            break;
        default:
            if (isalpha(l->ch)) {
                tok.literal = readIdentifier(l);
                tok.type = lookup_ident(tok.literal);
                return tok; // Возвращаем сразу, так как readIdentifier уже сдвинул позицию
            } else if (isdigit(l->ch)) {
                tok.literal = readNumber(l);
                tok.type = TOK_INT;
                return tok;
            } else {
                tok = newToken(TOK_ILLEGAL, &l->ch);
            }
            break;
    }

    readChar(l);
    return tok;
}