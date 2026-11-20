#include "ast_simple.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

Node* create_int_node(long value) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL; // Проверка на ошибку выделения памяти
    
    n->type = NODE_INT;
    n->int_value = value;
    n->left = NULL;
    n->right = NULL;
    n->op = 0;
    
    return n;
}

Node* create_binop_node(char op, Node* left, Node* right) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    
    n->type = NODE_BINOP;
    n->op = op;
    n->left = left;
    n->right = right;
    n->int_value = 0; // Не используется для операций
    
    return n;
}

Node* create_identifier_node(const char* name) {
    Node* n = (Node*)malloc(sizeof(Node)); // AST пока на malloc, объекты значений на арене
    if (!n) return NULL;
    
    n->type = NODE_IDENTIFIER;
    n->identifier_name = strdup(name); // Или можно тоже в арену, если хочешь всё туда
    
    // Инициализация остальных полей
    n->int_value = 0;
    n->left = NULL;
    n->right = NULL;
    n->op = 0;
    
    return n;
}

void free_node(Node* node) {
    if (!node) return;
    
    // Если это операция, сначала освобождаем детей
    if (node->type == NODE_BINOP) {
        free_node(node->left);
        free_node(node->right);
    }
    
    // Освобождаем саму структуру
    free(node);
}
const char* node_type_to_string(NodeType type) {
    switch(type) {
        case NODE_INT: return "INT";
        case NODE_BINOP: return "BINOP";
        default: return "UNKNOWN";
    }
}

void print_node(Node* node) {
    if (!node) return;

    if (node->type == NODE_BINOP) {
        // Выводим сам узел операции
        printf("[Node: %s] Operator: '%c'\n", 
               node_type_to_string(node->type), 
               node->op);
        
        // Рекурсивно идем влево и вправо
        // Добавляем отступы, чтобы видеть структуру дерева визуально
        printf("  Left:\n");
        print_node(node->left);
        printf("  Right:\n");
        print_node(node->right);
        
    } else if (node->type == NODE_INT) {
        // Выводим значение числа
        printf("[Node: %s] Value: %ld\n", 
               node_type_to_string(node->type), 
               node->int_value);
    }
}