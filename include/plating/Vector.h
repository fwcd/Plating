#include "StringBuffer.h"

/**
 * A weakly typed, dynamically growing array
 * of heap-allocated values.
 */
typedef struct {
	void** elements;
	int count;
	int allocatedCount;
	int chunkSize;
} Vector;

/** Creates and initializes a new vector of the heap */
Vector* VectorNew(void);

/** Appends an element to the end of the vector */
void VectorPush(Vector* self, void* element);

/**
 * Removes and returns the last element in the
 * vector. It does NOT call free upon it.
 * Returns NULL if the vector is empty.
 */
void* VectorPop(Vector* self);

/**
 * Fetches the pointer to an element by index.
 * Returns NULL if the index is out of bounds.
 */
void* VectorGet(Vector* self, int index);

/**
 * Removes an element by index and returns a pointer to it.
 * It does NOT call free upon it. (Use VectorRemoveFree in this case)
 * Does nothing and returns NULL if the index is out of bounds.
 */
void* VectorRemove(Vector* self, int index);

/**
 * Removes an element by index and frees it.
 * Does nothing if the index is out of bounds.
 */
void VectorRemoveFree(Vector* self, int index);

/** Frees the vector, but NOT the elements themselves */
void VectorDelete(Vector* self);

/** 
 * Frees the vector and all elements. Be careful
 * with this method as the elements might hold
 * pointers to resources themselves that could get leaked.
 */
void VectorDeleteDeeply(Vector* self);
