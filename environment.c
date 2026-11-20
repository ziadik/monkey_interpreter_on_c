#include "environment.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Environment* NewEnvironment(Arena* arena) {
    Environment* env = (Environment*)ArenaAlloc(arena, sizeof(Environment));
    if (!env) return NULL;
    
    env->count = 0;
    env->arena = arena;
    return env;
}

void EnvSet(Environment* env, const char* name, Object* value) {
    // Проверяем, есть ли уже такая переменная
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->bindings[i].name, name) == 0) {
            env->bindings[i].value = value;
            return;
        }
    }
    
    // Если нет - добавляем новую
    if (env->count < MAX_VARS) {
        // Копируем имя строки в арену, чтобы оно жило там же
        size_t len = strlen(name);
        char* new_name = (char*)ArenaAlloc(env->arena, len + 1);
        strcpy(new_name, name);
        
        env->bindings[env->count].name = new_name;
        env->bindings[env->count].value = value;
        env->count++;
    } else {
        printf("Error: Environment full!\n");
    }
}

Object* EnvGet(Environment* env, const char* name) {
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->bindings[i].name, name) == 0) {
            return env->bindings[i].value;
        }
    }
    return NULL; // Переменная не найдена
}