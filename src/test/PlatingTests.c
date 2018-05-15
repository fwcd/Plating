#include <stdio.h>
#include "../main/structs/HashMap.h"

typedef char* string;
DECLARE_HASH_MAP(string, string); // TODO: Debug this segmentation fault

int stringHasher(string value) {
	return value[0];
}

int main(void) {
	int bucketCount = 3;
	HashMap_string_string* map = HashMap_string_stringNew(bucketCount, stringHasher);
	HashMap_string_stringInsert(map, "testKey", "someValue");
	HashMap_string_stringInsert(map, "anotherKey", "otherValue");

	printf(HashMap_string_stringGet(map, "Non-existent key", "Default value 1"));
	printf(HashMap_string_stringGet(map, "testKey", "Default value 2"));
	printf(HashMap_string_stringGet(map, "anotherKey", "Default value 3"));

	HashMap_string_stringDelete(map);

	return 0;
}