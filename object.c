#include "object.h"
#include <stdlib.h>

Object* NewInteger(Arena* arena, long value) {
    // Выделяем память из арены, а не через malloc
    Object* obj = (Object*)ArenaAlloc(arena, sizeof(Object));
    if (!obj) return NULL;
    
    obj->type = OBJ_INT;
    obj->value.intValue = value;
    return obj;
}

Object* NewBoolean(Arena* arena, int value) {
    Object* obj = (Object*)ArenaAlloc(arena, sizeof(Object));
    if (!obj) return NULL;
    
    obj->type = OBJ_BOOL;
    obj->value.boolValue = value;
    return obj;
}

// Поскольку память освобождается при DestroyArena, 
// нам больше не нужен ручной free для каждого объекта.
void FreeObject(Object* obj) {
    // Do nothing - managed by Arena
}