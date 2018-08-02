#include "plating/MemoryUtils.h"

MemoryTracker MEM_TRACKER = {.allocations = 0};

void* memAlloc(size_t memSize) {
	MEM_TRACKER.allocations++;
	return malloc(memSize);
}

void memFree(void* memPtr) {
	MEM_TRACKER.allocations--;
	free(memPtr);
}
