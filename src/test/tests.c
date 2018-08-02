#include <stdio.h>

#include "plating/LogLevel.h"
#include "plating/LogAPI.h"
#include "plating/MemoryUtils.h"

#include "HashMapTest.h"
#include "LinkedListTest.h"
#include "VectorTest.h"
#include "StringBufferTest.h"

int main(void) {
	platingLogLevel = LOG_LEVEL_INFO;

	testHashMap();
	testLinkedList();
	testVector();
	testStringBuffer();
	logDebug("Leaked memory allocations before termination: %d", MEM_TRACKER.allocations);
	return 0;
}
