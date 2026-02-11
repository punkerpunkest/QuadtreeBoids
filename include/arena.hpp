#pragma once
#include <cstdint>
#include <cstddef>

struct Arena {
    Arena* next;
    size_t size;
    size_t capacity;
    uint8_t* data;
};

Arena* createArena(size_t capacity);
void* allocArena(Arena* arena, size_t bytes, size_t alignment = 8);
void resetArena(Arena* arena);
void freeArena(Arena* arena);

template<typename T>
T* allocArenaType(Arena* arena) {
    return static_cast<T*>(allocArena(arena, sizeof(T), alignof(T)));
}