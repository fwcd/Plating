#include <stdio.h>

#include "plating/LogLevel.h"
#include "plating/LogAPI.h"
#include "plating/MemoryUtils.h"

#include "HashMapTest.h"
#include "LinkedListTest.h"

int main(void) {
	platingLogLevel = LOG_LEVEL_DEEP_TRACE;

	testHashMap();
	testLinkedList();
	logDebug("Leaked memory allocations before termination: %d", MEM_TRACKER.allocations);
	return 0;
}
