#include "plating/Vector.h"
#include "plating/MemoryUtils.h"
#include <stdbool.h>

Vector* VectorNewWithCount(int initialCount) {
	Vector* instance = memAlloc(sizeof(Vector));
	instance->elements = memAlloc(sizeof(void*) * initialCount);
	instance->count = 0;
	instance->allocatedCount = initialCount;
	instance->chunkSize = initialCount;
	return instance;
}

Vector* VectorNew(void) {
	return VectorNewWithCount(10);
}

void VectorPush(Vector* self, void* element) {
	if (self->count >= self->allocatedCount) {
		// There is not enough space, so
		// we need to reallocate
		int newAllocatedCount = self->count + self->chunkSize;
		size_t newSize = sizeof(void*) * newAllocatedCount;
		void** newElements = memRealloc(self->elements, newSize);
		
		self->elements = newElements;
		self->allocatedCount = newAllocatedCount;
	}
	
	int index = self->count;
	
	self->elements[index] = element;
	self->count++;
}

void* VectorPop(Vector* self) {
	if (self->count == 0) {
		return NULL;
	} else {
		int index = self->count - 1;
		void* element = self->elements[index];
		self->elements[index] = NULL;
		self->count--;
		return element;
	}
}

bool VectorIndexInBounds(Vector* self, int index) {
	return (index >= 0) && (index < self->count);
}

void* VectorGet(Vector* self, int index) {
	if (!VectorIndexInBounds(self, index)) {
		// Return null pointer when out of bounds
		return NULL;
	} else {
		return self->elements[index];
	}
}

void* VectorRemove(Vector* self, int index) {
	if (!VectorIndexInBounds(self, index)) {
		// Return null pointer when out of bounds
		return NULL;
	}
	
	void* element = self->elements[index];
	
	for (int i=index+1; i<self->count; i++) {
		self->elements[i - 1] = self->elements[i];
	}
	
	self->count--;
	return element;
}

void VectorRemoveFree(Vector* self, int index) {
	void* removed = VectorRemove(self, index);
	if (removed != NULL) {
		memFree(removed);
	}
}

void VectorDelete(Vector* self) {
	memFree(self->elements);
	memFree(self);
}

void VectorDeleteDeeply(Vector* self) {
	for (int i=0; i<self->count; i++) {
		memFree(self->elements[i]);
	}
	memFree(self->elements);
	memFree(self);
}
