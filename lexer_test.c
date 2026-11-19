#include "test.h"
#include "lexer.h"
#include "token.h"
#include <string.h>

// Вспомогательная функция для сравнения типов токенов
const char* token_type_to_string(TokenType type) {
    switch(type) {
        case TOK_ILLEGAL: return "ILLEGAL";
        case TOK_EOF: return "EOF";
        case TOK_IDENT: return "IDENT";
        case TOK_INT: return "INT";
        case TOK_ASSIGN: return "=";
        case TOK_PLUS: return "+";
        case TOK_MINUS: return "-";
        case TOK_BANG: return "!";
        case TOK_ASTERISK: return "*";
        case TOK_SLASH: return "/";
        case TOK_LT: return "<";
        case TOK_GT: return ">";
        case TOK_EQ: return "==";
        case TOK_NOT_EQ: return "!=";
        case TOK_COMMA: return ",";
        case TOK_SEMICOLON: return ";";
        case TOK_LPAREN: return "(";
        case TOK_RPAREN: return ")";
        case TOK_LBRACE: return "{";
        case TOK_RBRACE: return "}";
        case TOK_FUNCTION: return "fn";
        case TOK_LET: return "let";
        case TOK_TRUE: return "true";
        case TOK_FALSE: return "false";
        case TOK_IF: return "if";
        case TOK_ELSE: return "else";
        case TOK_RETURN: return "return";
        default: return "UNKNOWN";
    }
}

void test_next_token_simple() {
    printf("\n--- Running Test: Simple Tokens ---\n");
    const char* input = "=+(){},;";
    Lexer* l = New(input);

    // Ожидаемые типы и литералы
    TokenType expected_types[] = {
        TOK_ASSIGN, TOK_PLUS, TOK_LPAREN, TOK_RPAREN, 
        TOK_LBRACE, TOK_RBRACE, TOK_COMMA, TOK_SEMICOLON, TOK_EOF
    };
    const char* expected_literals[] = {
        "=", "+", "(", ")", "{", "}", ",", ";", ""
    };

    for (int i = 0; i < 9; i++) {
        Token tok = NextToken(l);
        
        // Проверяем тип
        char msg[100];
        sprintf(msg, "Token[%d] Type mismatch", i);
        ASSERT_INT_EQ(msg, expected_types[i], tok.type);

        // Проверяем литерал
        sprintf(msg, "Token[%d] Literal mismatch", i);
        ASSERT_STR_EQ(msg, expected_literals[i], tok.literal);

        FreeToken(&tok);
    }
    free(l);
}

void test_let_statement() {
    printf("\n--- Running Test: Let Statement ---\n");
    const char* input = "let x = 5;";
    Lexer* l = New(input);

    struct {
        TokenType type;
        const char* literal;
    } expected[] = {
        {TOK_LET, "let"},
        {TOK_IDENT, "x"},
        {TOK_ASSIGN, "="},
        {TOK_INT, "5"},
        {TOK_SEMICOLON, ";"},
        {TOK_EOF, ""}
    };

    for (int i = 0; i < 6; i++) {
        Token tok = NextToken(l);
        
        char msg[100];
        sprintf(msg, "Let Stmt Token[%d] Type", i);
        ASSERT_INT_EQ(msg, expected[i].type, tok.type);

        sprintf(msg, "Let Stmt Token[%d] Literal", i);
        ASSERT_STR_EQ(msg, expected[i].literal, tok.literal);

        FreeToken(&tok);
    }
    free(l);
}

void test_keywords_and_identifiers() {
    printf("\n--- Running Test: Keywords vs Identifiers ---\n");
    const char* input = "fn let true false myVar";
    Lexer* l = New(input);

    struct {
        TokenType type;
        const char* literal;
    } expected[] = {
        {TOK_FUNCTION, "fn"},
        {TOK_LET, "let"},
        {TOK_TRUE, "true"},
        {TOK_FALSE, "false"},
        {TOK_IDENT, "myVar"},
        {TOK_EOF, ""}
    };

    for (int i = 0; i < 6; i++) {
        Token tok = NextToken(l);
        
        char msg[100];
        sprintf(msg, "Keywords Token[%d] Type", i);
        ASSERT_INT_EQ(msg, expected[i].type, tok.type);

        sprintf(msg, "Keywords Token[%d] Literal", i);
        ASSERT_STR_EQ(msg, expected[i].literal, tok.literal);

        FreeToken(&tok);
    }
    free(l);
}

void test_two_char_tokens() {
    printf("\n--- Running Test: Two Character Tokens ---\n");
    const char* input = "== != = !";
    Lexer* l = New(input);

    struct {
        TokenType type;
        const char* literal;
    } expected[] = {
        {TOK_EQ, "=="},
        {TOK_NOT_EQ, "!="},
        {TOK_ASSIGN, "="},
        {TOK_BANG, "!"},
        {TOK_EOF, ""}
    };

    for (int i = 0; i < 5; i++) {
        Token tok = NextToken(l);
        
        char msg[100];
        sprintf(msg, "TwoChar Token[%d] Type", i);
        ASSERT_INT_EQ(msg, expected[i].type, tok.type);

        sprintf(msg, "TwoChar Token[%d] Literal", i);
        ASSERT_STR_EQ(msg, expected[i].literal, tok.literal);

        FreeToken(&tok);
    }
    free(l);
}

void test_arithmetic() {
    printf("\n--- Running Test: Arithmetic ---\n");
    const char* input = "1 + 2 * 3;";
    Lexer* l = New(input);

    struct {
        TokenType type;
        const char* literal;
    } expected[] = {
        {TOK_INT, "1"},
        {TOK_PLUS, "+"},
        {TOK_INT, "2"},
        {TOK_ASTERISK, "*"},
        {TOK_INT, "3"},
        {TOK_SEMICOLON, ";"},
        {TOK_EOF, ""}
    };

    for (int i = 0; i < 7; i++) {
        Token tok = NextToken(l);
        
        char msg[100];
        sprintf(msg, "Arithmetic Token[%d] Type", i);
        ASSERT_INT_EQ(msg, expected[i].type, tok.type);

        sprintf(msg, "Arithmetic Token[%d] Literal", i);
        ASSERT_STR_EQ(msg, expected[i].literal, tok.literal);

        FreeToken(&tok);
    }
    free(l);
}

int main() {
    printf("Starting Monkey Interpreter Tests...\n");

    RUN_TEST(test_next_token_simple);
    RUN_TEST(test_let_statement);
    RUN_TEST(test_keywords_and_identifiers);
    RUN_TEST(test_two_char_tokens);
    RUN_TEST(test_arithmetic);

    printf("\n========================================\n");
    printf("Tests Run:    %d\n", tests_run);
    printf("Tests Passed: %d\n", tests_passed);
    printf("Tests Failed: %d\n", tests_run - tests_passed);
    printf("========================================\n");

    return (tests_run == tests_passed) ? 0 : 1;
}