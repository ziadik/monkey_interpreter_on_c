#ifndef AST_SIMPLE_H
#define AST_SIMPLE_H

#include "token.h" // Подключаем наши токены из предыдущих шагов

// Типы узлов для начала
typedef enum {
    NODE_INT,
    NODE_BINOP,
    NODE_IDENTIFIER 
} NodeType;

typedef struct Node {
    NodeType type;
    long int_value; 
    struct Node* left;  
    struct Node* right; 
    char op;            
    char* identifier_name; 
} Node;

// Функция создания узла-числа
Node* create_int_node(long value);

// Функция создания узла-операции
Node* create_binop_node(char op, Node* left, Node* right);

Node* create_identifier_node(const char* name);

// Функция освобождения памяти (важно!)
void free_node(Node* node);

// Функция для вывода на экран дерева
void print_node(Node* node);

#endif