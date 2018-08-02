#include <stdio.h>

#include "plating/LogLevel.h"
#include "plating/LogAPI.h"
#include "plating/MemoryUtils.h"

#include "HashMapTest.h"
#include "LinkedListTest.h"
#include "VectorTest.h"
#include "StringBufferTest.h"
#include "FileReaderTest.h"

int main(int argc, char* argv[]) {
	platingLogLevel = LOG_LEVEL_INFO;
	if (argc == 2) {
		const char* testResourcesFolder = argv[1];
		
		logInfo("--- Running Tests ---");
		testHashMap();
		testLinkedList();
		testVector();
		testStringBuffer();
		testFileReader(testResourcesFolder);
		logDebug("Leaked memory allocations before termination: %d", MEM_TRACKER.allocations);
	} else {
		logError("Incorrect number of arguments.");
		logError("Usage: o2ctest [folder of test resources]");
	}
	return 0;
}
