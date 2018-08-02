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

	string defaultVal = "Some default value";
	assertStrEq(defaultVal, LinkedList_stringGet(list, -1, defaultVal));
	assertStrEq(defaultVal, LinkedList_stringGet(list, 6, defaultVal));
	assertStrEq("entry0", LinkedList_stringGet(list, 0, defaultVal));
	assertStrEq("entry1", LinkedList_stringGet(list, 1, defaultVal));
	assertStrEq("entry2", LinkedList_stringGet(list, 2, defaultVal));
	assertStrEq("entry3", LinkedList_stringGet(list, 3, defaultVal));
	assertStrEq("entry4", LinkedList_stringGet(list, 4, defaultVal));
	assertStrEq("entry5", LinkedList_stringGet(list, 5, defaultVal));

	LinkedList_stringDelete(list);
	assertLeaks(0);
	pass("LinkedList");
}

#endif // PLATING_LINKED_LIST_TEST_H
