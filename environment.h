#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "object.h"
#include "arena.h"

// Максимальное количество переменных в окружении (для упрощения)
#define MAX_VARS 100

typedef struct {
    char* name;       // Имя переменной
    Object* value;    // Значение (объект из арены!)
} Binding;

typedef struct {
    Binding bindings[MAX_VARS];
    int count;        // Текущее количество переменных
    Arena* arena;     // Ссылка на арену для создания новых объектов
} Environment;

// Функции для работы с окружением
Environment* NewEnvironment(Arena* arena);
void EnvSet(Environment* env, const char* name, Object* value);
Object* EnvGet(Environment* env, const char* name);

#endif