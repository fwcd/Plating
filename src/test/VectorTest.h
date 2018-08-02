#ifndef PLATING_VECTOR_H
#define PLATING_VECTOR_H

#include "plating/TestUtils.h"
#include "plating/Vector.h"
#include "plating/MemoryUtils.h"

void testVector(void) {
	Vector* vec = VectorNew();
	assertPtrEq(NULL, VectorPop(vec));
	assertIntEq(0, vec->count);
	assertIntEq(10, vec->allocatedCount);
	
	for (int i=0; i<20; i++) {
		int* value = memAlloc(sizeof(int));
		*value = i;
		assertIntEq(i, vec->count);
		VectorPush(vec, value);
	}
	assertIntEq(20, vec->count);
	
	int* a = VectorPop(vec);
	int* b = VectorPop(vec);
	assertIntEq(19, *a);
	assertIntEq(18, *b);
	memFree(a);
	memFree(b);
	
	VectorRemoveFree(vec, 3);
	VectorRemoveFree(vec, 0);
	VectorDeleteDeeply(vec);
	assertLeaks(0);
	pass("Vector");
}

#endif // PLATING_VECTOR_H
