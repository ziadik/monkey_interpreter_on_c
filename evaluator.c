#include "evaluator.h"
#include <stdio.h>

Object* Eval(Node* node, Arena* arena) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_INT:
            // Вместо NewInteger(value), который делал malloc,
            // мы теперь создаем объект напрямую из арены
            Object* intObj = (Object*)ArenaAlloc(arena, sizeof(Object));
            intObj->type = OBJ_INT;
            intObj->value.intValue = node->int_value;
            return intObj;
        
        case NODE_BINOP:
            // Рекурсивно вычисляем левую и правую части, передавая арену
            Object* leftObj = Eval(node->left, arena);
            Object* rightObj = Eval(node->right, arena);
            
            if (!leftObj || !rightObj) return NULL;
            
            // Проверяем типы (как раньше)
            if (leftObj->type != OBJ_INT || rightObj->type != OBJ_INT) {
                printf("Error: Type mismatch\n");
                return NULL;
            }
            
            // Вычисляем результат
            long result = 0;
            switch (node->op) {
                case '+': result = leftObj->value.intValue + rightObj->value.intValue; break;
                case '-': result = leftObj->value.intValue - rightObj->value.intValue; break;
                case '*': result = leftObj->value.intValue * rightObj->value.intValue; break;
                case '/': 
                    if (rightObj->value.intValue == 0) return NULL;
                    result = leftObj->value.intValue / rightObj->value.intValue; 
                    break;
                default: return NULL;
            }
            
            // Создаем новый объект результата из арены
            Object* resObj = (Object*)ArenaAlloc(arena, sizeof(Object));
            resObj->type = OBJ_INT;
            resObj->value.intValue = result;
            return resObj;
            
        default:
            return NULL;
    }
}