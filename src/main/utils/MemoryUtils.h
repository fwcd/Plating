#ifndef PLATING_UTILS_MEMORY_UTILS_H
#define PLATING_UTILS_MEMORY_UTILS_H

#include <stdlib.h>

typedef struct MemoryTracker {
	int allocations;
} MemoryTracker;

static MemoryTracker MEM_TRACKER = {.allocations = 0};

void* memAlloc(size_t memSize) {
	MEM_TRACKER.allocations++;
	return malloc(memSize);
}

void memFree(void* memPtr) {
	MEM_TRACKER.allocations--;
	free(memPtr);
}

#endif // PLATING_UTILS_MEMORY_UTILS_H