#ifndef ARENA_H
#define ARENA_H

#include <stddef.h> // size_t

typedef struct {
    char* start;      // Начало блока памяти
    char* current;    // Текущая позиция для выделения
    size_t capacity;  // Общая емкость блока
} Arena;

// Создать арену размером capacity байт
Arena* CreateArena(size_t capacity);

// Выделить memory из арены
void* ArenaAlloc(Arena* arena, size_t size);

// Уничтожить арену (освободить всю память разом)
void DestroyArena(Arena* arena);

#endif