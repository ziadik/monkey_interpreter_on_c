#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

// Помощник: переход к следующему токену
static void nextToken(Parser* p) {
    if (p->currentToken.literal) free(p->currentToken.literal);
    p->currentToken = p->peekToken;
    p->peekToken = NextToken(p->lexer);
}

Parser* NewParser(Lexer* l) {
    Parser* p = (Parser*)malloc(sizeof(Parser));
    p->lexer = l;
    
    // Инициализация двух токенов
    p->currentToken = NextToken(l);
    p->peekToken = NextToken(l);
    
    return p;
}

void FreeParser(Parser* p) {
    if (p->currentToken.literal) free(p->currentToken.literal);
    if (p->peekToken.literal) free(p->peekToken.literal);
    free(p);
}

// Функция для проверки типа текущего токена
static int curTokenIs(Parser* p, TokenType type) {
    return p->currentToken.type == type;
}

// Функция для проверки типа следующего токена
static int peekTokenIs(Parser* p, TokenType type) {
    return p->peekToken.type == type;
}

// Ожидание конкретного токена
static int expectPeek(Parser* p, TokenType type) {
    if (peekTokenIs(p, type)) {
        nextToken(p);
        return 1; // true
    } else {
        printf("ERROR: Expected token type %d, got %d\n", type, p->peekToken.type);
        return 0; // false
    }
}

// Парсинг целого числа
static Node* parseIntegerLiteral(Parser* p) {
    long value = atol(p->currentToken.literal);
    return create_int_node(value);
}

// Основная функция парсинга выражения
Node* ParseExpression(Parser* p) {
    Node* leftExp = NULL;

    // 1. Проверяем, что текущий токен - число
    if (curTokenIs(p, TOK_INT)) {
        leftExp = parseIntegerLiteral(p);
    } else {
        printf("ERROR: Unexpected token in expression start: %s\n", p->currentToken.literal);
        return NULL;
    }

    // 2. Проверяем, есть ли после числа оператор (+ или -)
    // Для простоты пока обрабатываем только '+'
    if (peekTokenIs(p, TOK_PLUS)) {
        char op = p->peekToken.literal[0]; // Получаем символ оператора
        
        // Продвигаемся к оператору
        nextToken(p); 
        
        // Продвигаемся к правому операнду
        nextToken(p);
        
        // Рекурсивно парсим правую часть (или просто ожидаем число)
        if (!curTokenIs(p, TOK_INT)) {
            printf("ERROR: Expected integer after operator\n");
            free_node(leftExp); // Освобождаем левую часть при ошибке
            return NULL;
        }
        
        Node* rightExp = parseIntegerLiteral(p);
        
        // Создаем бинарную операцию
        leftExp = create_binop_node(op, leftExp, rightExp);
    }

    return leftExp;
}