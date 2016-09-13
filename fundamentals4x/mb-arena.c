#include "membench.h"
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

/*

Write an arena allocator for `chunk` objects. Your allocator should:

* Allocate a chunk in O(1) time.
* Free a chunk in O(1) time.
* Use memory proportional to the peak number of actively allocated
chunks (rather than, say, the total number of allocated chunks).
* Run out of memory only if the system has no more memory available.

More on arenas:
https://en.wikipedia.org/wiki/Region-based_memory_management

See "membench.h" for function semantics.

*/

typedef struct free_chunk {
    struct free_chunk* next;
} free_chunk;

// A `chunk_or_free` object is *either* an allocated chunk, *or* a
// free chunk. That calls for a union!
typedef union chunk_or_free {
    chunk c;
    free_chunk f;
} chunk_or_free;

#define GROUPSIZE 4096
typedef struct membench_group {
    chunk_or_free chunks[GROUPSIZE];
    struct membench_group* next;
} membench_group;

struct membench_arena {
    free_chunk* free_chunks;
    membench_group* group;
};


static membench_group* membench_group_new(membench_arena* arena) {
    membench_group* g = (membench_group*) malloc(sizeof(membench_group));
    for (int i = 0; i < GROUPSIZE; i++) {
        free_chunk* chunk = &g->chunks[i].f;
        chunk->next = arena->free_chunks;
        arena->free_chunks = chunk;
    }
    return g;
}

membench_arena* membench_arena_create(void) {
    membench_arena* arena = (membench_arena*) malloc(sizeof(membench_arena));
    arena->free_chunks = NULL;
    arena->group = membench_group_new(arena);
    return arena;
}

chunk* membench_alloc(membench_arena* arena) {
    membench_group* g = arena->group;
    if (arena->free_chunks == NULL) {
        // allocate new group, add it to singly-linked group list
        g = membench_group_new(arena);
        g->next = arena->group;
        arena->group = g;
    }
    free_chunk* result = arena->free_chunks;
    arena->free_chunks = result->next;
    return (chunk*) result;
}

void membench_free(membench_arena* arena, chunk* x) {
    free_chunk* new_free = (free_chunk*) x;
    new_free->next = arena->free_chunks;
    arena->free_chunks = new_free;
}

void membench_arena_destroy(membench_arena* arena) {
    membench_group* g;
    while ((g = arena->group)) {
        arena->group = g->next;
        free(g);
    }
    free(arena);
}
