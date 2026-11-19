#ifndef AST_H
#define AST_H

#include "token.h"
#include <stdio.h> // Для printf/char*

typedef enum {
    NODE_PROGRAM,
    NODE_LET_STATEMENT,
    NODE_IDENTIFIER,
    NODE_INTEGER_LITERAL,
    NODE_EXPRESSION_STATEMENT,
    NODE_INTEGER_LITERAL, // Число 5
    NODE_IDENTIFIER,    // Переменная x
    NODE_INFIX_EXPRESSION, // 5 + 5
    NODE_PREFIX_EXPRESSION, // -5
    // ... добавляем по мере необходимости
} NodeType;

// Базовая структура узла
typedef struct Node {
    NodeType type;
    Token token; // Храним токен для отладки
    
    // Здесь мы могли бы использовать union, но пока оставим указатели
    // или специфичные поля для простоты понимания архитектуры.
    
    // Пример для LetStatement:
    char* name; // Указатель на имя переменной
    struct Node* value; // Указатель на выражение справа от "="
    void* specific_data; 
    
} Node;

// Пример для LetStatement
typedef struct {
    char* name;      // Имя переменной (например, "x")
    Node* value;     // Выражение справа от "=" (например, IntegerLiteral)
} LetStatementData;

// Пример для IntegerLiteral
typedef struct {
    long value;      // Число (в C используем long вместо int64)
} IntegerLiteralData;

// Пример для InfixExpression
typedef struct {
    Node* left;      // Левая часть
    char* operator;  // Оператор ("+", "-", "*")
    Node* right;     // Правая часть
} InfixExpressionData;

// Функция для создания нового узла
Node* NewNode(NodeType type, Token tok);

// Функция для освобождения памяти дерева
void FreeNode(Node* node);

#endif