#ifndef OBJECT_H
#define OBJECT_H

#include "arena.h" // Подключаем арену

typedef enum {
    OBJ_INT,
    OBJ_BOOL,
    OBJ_NULL,
    // ... другие типы
} ObjectType;

typedef struct Object {
    ObjectType type;
    union {
        long intValue;
        int boolValue;
    } value;
} Object;

// Теперь функции принимают арену как аргумент
Object* NewInteger(Arena* arena, long value);
Object* NewBoolean(Arena* arena, int value);
void FreeObject(Object* obj); // Эта функция теперь может быть пустой или удаленной!

#endif