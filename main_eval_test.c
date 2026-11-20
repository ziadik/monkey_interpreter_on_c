#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "evaluator.h"
#include "arena.h"
#include "environment.h"
#include "ast_simple.h"

int main() {
    char* input = "5 + x"; // Представим, что x определен выше
    
    Lexer* l = New(input);
    Parser* p = NewParser(l);
    
    // Для простоты теста построим AST вручную, так как парсер пока не умеет 'let'
    // Но сначала создадим инфраструктуру
    
    Arena* arena = CreateArena(1024 * 1024);
    Environment* env = NewEnvironment(arena);
    
    // 1. Кладем переменную x = 10 в окружение
    Object* tenObj = (Object*)ArenaAlloc(arena, sizeof(Object));
    tenObj->type = OBJ_INT;
    tenObj->value.intValue = 10;
    EnvSet(env, "x", tenObj);
    
    // 2. Строим дерево для выражения "5 + x" вручную
    Node* fiveNode = create_int_node(5);
    Node* xNode = create_identifier_node("x"); // Используем твою функцию из прошлого шага
    Node* plusNode = create_binop_node('+', fiveNode, xNode);
    
    // 3. Оцениваем
    printf("--- Evaluating 5 + x (where x=10) ---\n");
    Object* result = Eval(plusNode, env, arena);
    
    if (result && result->type == OBJ_INT) {
        printf("Result: %ld\n", result->value.intValue); // Должно быть 15
    } else {
        printf("Evaluation failed.\n");
    }
    
    // Очистка
    free_node(plusNode); // Освобождаем AST (он был на malloc)
    DestroyArena(arena); // Освобождаем объекты и окружение
    
    FreeParser(p);
    free(l);
    return 0;
}