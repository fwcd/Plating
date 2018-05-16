#include <stdio.h>

#include "../main/utils/LogLevels.h"
#define LOG_LEVEL LOG_LEVEL_DEEP_TRACE
#include "../main/utils/Logger.h"

#include "../main/structs/HashMap.h"
#include "../main/utils/MemoryUtils.h"


typedef char* string;
DECLARE_HASH_MAP(string, string); // TODO: Debug this segmentation fault

int stringHasher(string value) {
	return (int) value[0];
}

void println(const char* msg) {
	printf(msg);
	printf("\n");
}

int main(void) {
	int bucketCount = 3;
	HashMap_string_string* map = HashMap_string_stringNew(bucketCount, stringHasher);
	HashMap_string_stringInsert(map, "keyA", "valueA");
	HashMap_string_stringInsert(map, "keyB", "valueB");
	HashMap_string_stringInsert(map, "keyC", "valueC");
	HashMap_string_stringInsert(map, "keyD", "valueD");
	HashMap_string_stringInsert(map, "keyE", "valueE");
	HashMap_string_stringInsert(map, "keyF", "valueF");

	println(HashMap_string_stringGet(map, "Non-existent key", "Expected default value"));
	println(HashMap_string_stringGet(map, "keyA", "Unexpected default value"));
	println(HashMap_string_stringGet(map, "keyB", "Unexpected default value"));
	println(HashMap_string_stringGet(map, "keyC", "Unexpected default value"));
	println(HashMap_string_stringGet(map, "keyD", "Unexpected default value"));
	println(HashMap_string_stringGet(map, "keyE", "Unexpected default value"));
	println(HashMap_string_stringGet(map, "keyF", "Unexpected default value"));

	HashMap_string_stringDelete(map);

	logTrace("Leaked memory allocations before termination: %d", MEM_TRACKER.allocations);
	return 0;
}