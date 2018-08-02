#include "plating/MemoryUtils.h"
#include "plating/LogAPI.h"

MemoryTracker MEM_TRACKER = {.allocations = 0};

void* memAlloc(size_t memSize) {
	MEM_TRACKER.allocations++;
	return malloc(memSize);
}

void* memRealloc(void* ptr, size_t size) {
	void* result = realloc(ptr, size);
	if (result == NULL) {
		logError("Reallocation failed!");
		return NULL;
	} else {
		return result;
	}
}

void memFree(void* memPtr) {
	MEM_TRACKER.allocations--;
	free(memPtr);
}
