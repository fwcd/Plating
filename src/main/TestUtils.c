#include "plating/TestUtils.h"
#include "plating/LogAPI.h"
#include "plating/MemoryUtils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void fail(void) {
	logError("=== TEST FAILED ===");
	exit(1);
}

void assertTrue(bool cond, const char* msg) {
	if (!cond) {
		logError("Assertion failed: %s", msg);
		fail();
	}
}

void assertFalse(bool cond, const char* msg) {
	assertTrue(!cond, msg);
}

void assertPtrEq(void* expected, void* actual) {
	if (actual != expected) {
		logError("Assertion failed: Expected pointer 0x%x, but was 0x%x", expected, actual);
		fail();
	}
}

void assertIntEq(int expected, int actual) {
	if (actual != expected) {
		logError("Assertion failed: Expected %d, but was %d", expected, actual);
		fail();
	}
}

void assertStrEq(const char* expected, const char* actual) {
	if (strcmp(actual, expected) != 0) {
		logError("Assertion failed: Expected \"%s\", but was \"%s\"", expected, actual);
		fail();
	}
}

void assertStringBufferEq(const char* expected, StringBuffer* actual) {
	char* bufContents = StringBufferGetCopy(actual);
	assertStrEq(expected, bufContents);
	memFree(bufContents);
}

void assertLeaks(int leaks) {
	if (MEM_TRACKER.allocations != leaks) {
		logError("Assertion failed: Expected %d leaks, but were %d", leaks, MEM_TRACKER.allocations);
		fail();
	}
}

void pass(const char* name) {
	logInfo("PASSED Test: %s", name);
}
