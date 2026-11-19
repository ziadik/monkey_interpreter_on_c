#include "arena.h"
#include <stdlib.h>
#include <stdio.h>

Arena* CreateArena(size_t capacity) {
    Arena* a = malloc(sizeof(Arena));
    if (!a) return NULL;
    
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
    // Проверка границ
    if (arena->current + size > arena->start + arena->capacity) {
        fprintf(stderr, "ERROR: Arena out of memory!\n");
        exit(1); // Или возвращать NULL и обрабатывать ошибку выше
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