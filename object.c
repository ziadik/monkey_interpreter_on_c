#include "object.h"
#include <stdlib.h>

Object* NewInteger(long value) {
    Object* obj = (Object*)malloc(sizeof(Object));
    if (!obj) return NULL;
    obj->type = OBJ_INT;
    obj->value.intValue = value;
    return obj;
}

Object* NewBoolean(int value) {
    Object* obj = (Object*)malloc(sizeof(Object));
    if (!obj) return NULL;
    obj->type = OBJ_BOOL;
    obj->value.boolValue = value;
    return obj;
}

void FreeObject(Object* obj) {
    if (obj) free(obj);
}