#include "ast_simple.h"
#include <stdlib.h> // Для malloc и free

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