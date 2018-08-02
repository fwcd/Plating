#ifndef PLATING_MEMORY_UTILS_H
#define PLATING_MEMORY_UTILS_H

#include <stdlib.h>

/*
 * Memory allocation wrapper that tracks
 * the number of allocations performed to
 * discover potential memory leaks.
 */

typedef struct MemoryTracker {
	int allocations;
} MemoryTracker;

extern MemoryTracker MEM_TRACKER;

/** Allocates memory of the given size and returns a pointer to it */
void* memAlloc(size_t memSize);

/**
 * Reallocates the memory pointed to with the
 * given size. Returns NULL if the reallocation
 * was unsuccessful.
 */
void* memRealloc(void* ptr, size_t size);

/** Frees the memory pointer to */
void memFree(void* memPtr);

#endif // PLATING_MEMORY_UTILS_H
