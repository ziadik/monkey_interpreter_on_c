#include <stdio.h>
#include <stdlib.h> 
#include "parser.h"
#include "lexer.h"
#include "ast_simple.h"


int main() {
    
    printf("\n--- Running: main parser test  ---\n");
    
    char* input = "5 + 10";
    
    printf("\n--- Init: Lexer  ---\n");
    Lexer* l = New(input);
    
    printf("\n--- Init: Parser  ---\n");
    Parser *p = NewParser(l);
    
    printf("\n--- Init: Node  ---\n");
    Node* n = ParseExpression(p);
    
    printf("\n--- Print: Node  ---\n");
    print_node(n);
    
    free_node(n);
    FreeParser(p);
    free(l);

    return 0;
}