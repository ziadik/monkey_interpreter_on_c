#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

typedef struct {
    char* start;
    char* current;
    size_t capacity;
} Arena;

Arena* CreateArena(size_t capacity);
void* ArenaAlloc(Arena* arena, size_t size);
void DestroyArena(Arena* arena);

#endif