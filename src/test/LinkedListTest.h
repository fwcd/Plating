#ifndef PLATING_LINKED_LIST_TEST_H
#define PLATING_LINKED_LIST_TEST_H

#include "plating/LinkedList.h"

typedef const char* string;
DECLARE_LINKED_LIST(string)

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

#endif // PLATING_LINKED_LIST_TEST_H
