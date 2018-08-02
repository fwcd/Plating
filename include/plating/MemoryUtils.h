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

void* memAlloc(size_t memSize);

void* memRealloc(void* ptr, size_t size);

void memFree(void* memPtr);

#endif // PLATING_MEMORY_UTILS_H
