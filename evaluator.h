#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ast_simple.h"
#include "object.h"
#include "arena.h" 
#include "environment.h"

// Теперь Eval принимает арену
Object* Eval(Node* node, Environment* env, Arena* arena);

#endif