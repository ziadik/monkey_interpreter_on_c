#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ast_simple.h"
#include "object.h"
#include "arena.h" // Подключаем арену

// Теперь Eval принимает арену
Object* Eval(Node* node, Arena* arena);

#endif