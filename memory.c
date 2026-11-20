#include "memory.h"
#include <stdlib.h>
#include <string.h>

Arena* CreateArena(size_t capacity) {
    Arena* a = malloc(sizeof(Arena));
    if (!a) return NULL;
    
    // Выделяем один большой кусок памяти
    a->start = malloc(capacity);
    if (!a->start) {
        free(a);
        return NULL;
    }
    
    a->current = a->start;
    a->capacity = capacity;
    return a;
}

void* ArenaAlloc(Arena* arena, size_t size) {
    // Проверяем, хватит ли места
    if (arena->current + size > arena->start + arena->capacity) {
        printf("ERROR: Arena full!\n");
        exit(1); // Для простоты падаем, если кончилась память
    }
    
    void* ptr = arena->current;
    arena->current += size;
    return ptr;
}

void DestroyArena(Arena* arena) {
    if (arena) {
        free(arena->start);
        free(arena);
    }
}