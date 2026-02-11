#include "arena.hpp"

Arena* createArena(size_t capacity){
    Arena* arena = new Arena();
    arena->next = nullptr;
    arena->capacity = capacity;
    arena->size = 0;
    arena->data = new uint8_t[capacity];
    return arena;
}

void* allocArena(Arena* arena, size_t bytes, size_t alignment){
    size_t padding = (alignment - (arena->size % alignment)) % alignment;
    size_t aligned_size = arena->size + padding;
    
    if (aligned_size + bytes <= arena->capacity){
        uint8_t* result = arena->data + aligned_size;
        arena->size = aligned_size + bytes;
        return result;
    }
    
    if (!arena -> next){
        arena->next = createArena(arena->capacity);
    }

    return allocArena(arena->next, bytes, alignment);
}

void resetArena(Arena* arena){
    while (arena){
        arena->size = 0;
        arena = arena->next;
    }
}

void freeArena(Arena* arena){
    while (arena){
        Arena* next = arena->next;
        delete[] arena->data;
        delete arena;
        arena = next;
    }
}
