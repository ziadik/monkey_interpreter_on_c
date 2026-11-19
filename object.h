#ifndef OBJECT_H
#define OBJECT_H

typedef enum {
    OBJ_INT,
    OBJ_BOOL,
    OBJ_NULL,
    // Позже добавим OBJ_STRING, OBJ_ARRAY и т.д.
} ObjectType;

// Базовая структура объекта
typedef struct Object {
    ObjectType type;
    
    // Для простоты пока используем union, чтобы не плодить malloc/free 
    // для каждого маленького числа. Это эффективнее и проще для обучения.
    union {
        long intValue;
        int boolValue;
    } value;
    
} Object;

// Функции-помощники для создания объектов
Object* NewInteger(long value);
Object* NewBoolean(int value); // 1 = true, 0 = false
void FreeObject(Object* obj);

#endif