#include "ast.h"
#include <stdlib.h>
#include <string.h>

Node* NewNode(NodeType type, Token tok) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    
    node->type = type;
    node->token = tok; // Копируем токен (помни про strdup в лексере!)
    node->specific_data = NULL;
    
    // Выделяем память под специфичные данные в зависимости от типа
    switch(type) {
        case NODE_LET_STATEMENT:
            node->specific_data = malloc(sizeof(LetStatementData));
            break;
        case NODE_INTEGER_LITERAL:
            node->specific_data = malloc(sizeof(IntegerLiteralData));
            break;
        case NODE_INFIX_EXPRESSION:
            node->specific_data = malloc(sizeof(InfixExpressionData));
            break;
        // ... другие типы
        default:
            // Для простых узлов может не требоваться доп. память
            break;
    }
    
    return node;
}

void FreeNode(Node* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_LET_STATEMENT: {
            LetStatementData* data = (LetStatementData*)node->specific_data;
            free(data->name); // Освобождаем строку имени
            FreeNode(data->value); // Рекурсивно освобождаем выражение
            free(data);
            break;
        }
        case NODE_INTEGER_LITERAL: {
            IntegerLiteralData* data = (IntegerLiteralData*)node->specific_data;
            // Нечего дополнительно освобождать внутри структуры
            free(data);
            break;
        }
        case NODE_INFIX_EXPRESSION: {
            InfixExpressionData* data = (InfixExpressionData*)node->specific_data;
            FreeNode(data->left);  // Рекурсивно
            free(data->operator);  // Освобождаем строку оператора
            FreeNode(data->right); // Рекурсивно
            free(data);
            break;
        }
        // ... другие типы
    }
    
    // Освобождаем токен (если он владеет памятью literal)
    if (node->token.literal) {
        free(node->token.literal);
    }
    
    free(node);
}