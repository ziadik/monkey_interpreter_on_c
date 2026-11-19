#ifndef AST_SIMPLE_H
#define AST_SIMPLE_H

#include "token.h" // Подключаем наши токены из предыдущих шагов

// Типы узлов для начала
typedef enum {
    NODE_INT,   // Целое число
    NODE_BINOP  // Бинарная операция (например, сложение)
} NodeType;

// Структура узла дерева
typedef struct Node {
    NodeType type;
    
    // Поля для NODE_INT
    long int_value; 
    
    // Поля для NODE_BINOP
    struct Node* left;  // Левый операнд
    struct Node* right; // Правый операнд
    char op;            // Оператор ('+', '-', '*', '/')
    
} Node;

// Функция создания узла-числа
Node* create_int_node(long value);

// Функция создания узла-операции
Node* create_binop_node(char op, Node* left, Node* right);

// Функция освобождения памяти (важно!)
void free_node(Node* node);

#endif