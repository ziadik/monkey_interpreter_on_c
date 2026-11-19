#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_ILLEGAL,
    TOK_EOF,
    TOK_IDENT, // add, foobar, x, y, ...
    TOK_INT,   // 1343456
    TOK_ASSIGN, // =
    TOK_PLUS,   // +
    TOK_MINUS,  // -
    TOK_BANG,   // !
    TOK_ASTERISK, // *
    TOK_SLASH,  // /
    TOK_LT,     // <
    TOK_GT,     // >
    TOK_EQ,     // ==
    TOK_NOT_EQ, // !=
    TOK_COMMA,  // ,
    TOK_SEMICOLON, // ;
    TOK_LPAREN, // (
    TOK_RPAREN, // )
    TOK_LBRACE, // {
    TOK_RBRACE, // }
    TOK_FUNCTION, // fn
    TOK_LET,      // let
    TOK_TRUE,     // true
    TOK_FALSE,    // false
    TOK_IF,       // if
    TOK_ELSE,     // else
    TOK_RETURN    // return
} TokenType;

typedef struct {
    TokenType type;
    char* literal; // Указатель на строку. В C мы должны сами управлять этой памятью!
} Token;

// Функция для проверки, является ли идентификатор ключевым словом
TokenType lookup_ident(const char* ident);

#endif