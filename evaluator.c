#include "evaluator.h"
#include <stdio.h>

Object* Eval(Node* node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_INT:
            // Если это число, просто создаем объект Integer
            return NewInteger(node->int_value);
        
        case NODE_BINOP:
            // Если это операция, сначала вычисляем левую и правую части
            Object* leftObj = Eval(node->left);
            Object* rightObj = Eval(node->right);
            
            if (!leftObj || !rightObj) return NULL;
            
            // Проверяем, что оба операнда - числа
            if (leftObj->type != OBJ_INT || rightObj->type != OBJ_INT) {
                printf("Error: Type mismatch in binary operation\n");
                FreeObject(leftObj);
                FreeObject(rightObj);
                return NULL;
            }
            
            // Выполняем операцию
            long result = 0;
            switch (node->op) {
                case '+':
                    result = leftObj->value.intValue + rightObj->value.intValue;
                    break;
                case '-':
                    result = leftObj->value.intValue - rightObj->value.intValue;
                    break;
                case '*':
                    result = leftObj->value.intValue * rightObj->value.intValue;
                    break;
                case '/':
                    if (rightObj->value.intValue == 0) {
                        printf("Error: Division by zero\n");
                        FreeObject(leftObj);
                        FreeObject(rightObj);
                        return NULL;
                    }
                    result = leftObj->value.intValue / rightObj->value.intValue;
                    break;
                default:
                    printf("Error: Unknown operator '%c'\n", node->op);
                    FreeObject(leftObj);
                    FreeObject(rightObj);
                    return NULL;
            }
            
            // Освобождаем промежуточные объекты
            FreeObject(leftObj);
            FreeObject(rightObj);
            
            // Возвращаем новый объект с результатом
            return NewInteger(result);
            
        default:
            printf("Error: Cannot evaluate node type %d\n", node->type);
            return NULL;
    }
}