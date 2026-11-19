#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "evaluator.h"
#include "arena.h"

int main() {
    char* input = "5 + 10 * 2"; 
    
    // 1. Создаем Лексер и Парсер (они пока используют обычный malloc для AST)
    Lexer* l = New(input);
    Parser* p = NewParser(l);
    
    // 2. Парсим выражение -> получаем Node (AST)
    Node* ast = ParseExpression(p);
    
    if (ast) {
        // 3. Создаем Арену для объектов значений
        // Размер 1 МБ достаточно для учебных целей
        Arena* arena = CreateArena(1024 * 1024); 
        
        printf("\n--- Evaluating with Arena ---\n");
        
        // 4. Передаем арену в Eval
        Object* result = Eval(ast, arena);
        
        if (result && result->type == OBJ_INT) {
            printf("Result: %ld\n", result->value.intValue);
        } else {
            printf("Evaluation failed.\n");
        }
        
        // 5. Освобождаем AST (так как он был создан через malloc в парсере)
        free_node(ast);
        
        // 6. Уничтожаем Арену (вся память объектов освобождается разом!)
        DestroyArena(arena);
    }
    
    FreeParser(p);
    free(l);
    return 0;
}