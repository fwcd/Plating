#ifndef PLATING_HASH_MAP_TEST_H
#define PLATING_HASH_MAP_TEST_H

#include "plating/TestUtils.h"
#include "plating/HashMap.h"
#include "plating/MemoryUtils.h"

typedef const char* string;
DECLARE_HASH_MAP(string, string);

int stringHasher(string value) {
	return (int) value[0];
}

void testHashMap(void) {
	int bucketCount = 3;
	HashMap_string_string* map = HashMap_string_stringNew(bucketCount, stringHasher);
	HashMap_string_stringInsert(map, "keyA", "valueA");
	HashMap_string_stringInsert(map, "keyB", "valueB");
	HashMap_string_stringInsert(map, "keyC", "valueC");
	HashMap_string_stringInsert(map, "keyD", "valueD");
	HashMap_string_stringInsert(map, "keyE", "valueE");
	HashMap_string_stringInsert(map, "keyF", "valueF");
	
	const char* defaultVal = "Default value";
	assertStrEq(defaultVal, HashMap_string_stringGet(map, "Non-existent key", defaultVal));
	assertStrEq("valueA", HashMap_string_stringGet(map, "keyA", defaultVal));
	assertStrEq("valueB", HashMap_string_stringGet(map, "keyB", defaultVal));
	assertStrEq("valueC", HashMap_string_stringGet(map, "keyC", defaultVal));
	assertStrEq("valueD", HashMap_string_stringGet(map, "keyD", defaultVal));
	assertStrEq("valueE", HashMap_string_stringGet(map, "keyE", defaultVal));
	assertStrEq("valueF", HashMap_string_stringGet(map, "keyF", defaultVal));

	HashMap_string_stringDelete(map);
	logDebug("Leaked memory allocations after HashMap testing: %d", MEM_TRACKER.allocations);
}

#endif // PLATING_HASH_MAP_TEST_H
