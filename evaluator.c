#include "evaluator.h"
#include <stdio.h>

#include "evaluator.h"
#include <stdio.h>

Object* Eval(Node* node, Environment* env, Arena* arena) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_INT:
            Object* intObj = (Object*)ArenaAlloc(arena, sizeof(Object));
            intObj->type = OBJ_INT;
            intObj->value.intValue = node->int_value;
            return intObj;
        
        case NODE_BINOP:
            Object* leftObj = Eval(node->left, env, arena);
            Object* rightObj = Eval(node->right, env, arena);
            
            if (!leftObj || !rightObj) return NULL;
            
            if (leftObj->type != OBJ_INT || rightObj->type != OBJ_INT) {
                printf("Error: Type mismatch\n");
                return NULL;
            }
            
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
            
            Object* resObj = (Object*)ArenaAlloc(arena, sizeof(Object));
            resObj->type = OBJ_INT;
            resObj->value.intValue = result;
            return resObj;

        // --- НОВАЯ ЧАСТЬ: Обработка Идентификаторов ---
        case NODE_IDENTIFIER:
            // Ищем имя переменной в окружении
            // Функция EnvGet возвращает указатель на Object или NULL, если не найдено
            Object* val = EnvGet(env, node->identifier_name);
            
            if (val == NULL) {
                printf("ERROR: identifier not found: %s\n", node->identifier_name);
                return NULL; // Или можно вернуть объект Error, как в книге
            }
            
            // Возвращаем найденное значение
            return val;
        // ----------------------------------------------

        default:
            printf("Error: Cannot evaluate node type %d\n", node->type);
            return NULL;
    }
}