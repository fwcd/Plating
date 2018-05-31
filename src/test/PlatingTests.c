#include <stdio.h>

#include "../main/utils/LogLevels.h"
#define LOG_LEVEL LOG_LEVEL_DEEP_TRACE
#include "../main/utils/Logger.h"

#include "../main/structs/HashMap.h"
#include "../main/structs/LinkedList.h"
#include "../main/utils/MemoryUtils.h"

typedef char* string;
DECLARE_HASH_MAP(string, string);
DECLARE_LINKED_LIST(string);

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

	logInfo(HashMap_string_stringGet(map, "Non-existent key", "Expected default value"));
	logInfo(HashMap_string_stringGet(map, "keyA", "Unexpected default value"));
	logInfo(HashMap_string_stringGet(map, "keyB", "Unexpected default value"));
	logInfo(HashMap_string_stringGet(map, "keyC", "Unexpected default value"));
	logInfo(HashMap_string_stringGet(map, "keyD", "Unexpected default value"));
	logInfo(HashMap_string_stringGet(map, "keyE", "Unexpected default value"));
	logInfo(HashMap_string_stringGet(map, "keyF", "Unexpected default value"));

	HashMap_string_stringDelete(map);
	logDebug("Leaked memory allocations after HashMap testing: %d", MEM_TRACKER.allocations);
}

void testLinkedList(void) {
	LinkedList_string* list = LinkedList_stringNew();
	LinkedList_stringPush(list, "entry0");
	LinkedList_stringPush(list, "entry1");
	LinkedList_stringPush(list, "entry2");
	LinkedList_stringPush(list, "entry3");
	LinkedList_stringPush(list, "entry4");
	LinkedList_stringPush(list, "entry5");

	logInfo(LinkedList_stringGet(list, -1, "Expected default value 1"));
	logInfo(LinkedList_stringGet(list, 6, "Expected default value 2"));
	logInfo(LinkedList_stringGet(list, 0, "Unexpected default value"));
	logInfo(LinkedList_stringGet(list, 1, "Unexpected default value"));
	logInfo(LinkedList_stringGet(list, 2, "Unexpected default value"));
	logInfo(LinkedList_stringGet(list, 3, "Unexpected default value"));
	logInfo(LinkedList_stringGet(list, 4, "Unexpected default value"));
	logInfo(LinkedList_stringGet(list, 5, "Unexpected default value"));

	LinkedList_stringDelete(list);
	logDebug("Leaked memory allocations after LinkedList testing: %d", MEM_TRACKER.allocations);
}

int main(void) {
	logInfo("=== Testing HashMap ===");
	testHashMap();

	logInfo("=== Testing LinkedList ===");
	testLinkedList();

	logDebug("Leaked memory allocations before termination: %d", MEM_TRACKER.allocations);
	return 0;
}