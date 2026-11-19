#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "evaluator.h"

int main() {
    char* input = "5 + 10 * 2"; // Давай усложним
    
    Lexer* l = New(input);
    Parser* p = NewParser(l);
    
    // Парсим выражение
    Node* ast = ParseExpression(p);
    
    if (ast) {
        printf("\n--- Evaluating ---\n");
        Object* result = Eval(ast);
        
        if (result && result->type == OBJ_INT) {
            printf("Result: %ld\n", result->value.intValue);
        } else {
            printf("Evaluation failed or not an integer.\n");
        }
        
        // Очистка памяти
        FreeObject(result);
        free_node(ast);
    }
    
    FreeParser(p);
    free(l);
    return 0;
}