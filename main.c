#include <stdio.h>
#include <stdlib.h>
#include "ast_simple.h"

int main() {
    printf("\n--- Running: main  ---\n");
    char* input = "5 + 10";
    Node* n5 = create_int_node(5);
    Node* n10 = create_int_node(10);
    Node* nPlus = create_binop_node('+',n5,n10);
    
    printf("\n--- Printing: Node  ---\n");
    print_node(nPlus);    
    
    printf("\n--- free: nPlus  ---\n");
    free_node(nPlus); 
    return 0;
}