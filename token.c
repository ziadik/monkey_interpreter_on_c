#include "token.h"
#include <string.h>

typedef struct {
    const char* literal;
    TokenType type;
} Keyword;

static Keyword keywords[] = {
    {"fn", TOK_FUNCTION},
    {"let", TOK_LET},
    {"true", TOK_TRUE},
    {"false", TOK_FALSE},
    {"if", TOK_IF},
    {"else", TOK_ELSE},
    {"return", TOK_RETURN}
};

static int num_keywords = sizeof(keywords) / sizeof(Keyword);

TokenType lookup_ident(const char* ident) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(ident, keywords[i].literal) == 0) {
            return keywords[i].type;
        }
    }
    return TOK_IDENT;
}