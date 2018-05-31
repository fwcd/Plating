#ifndef PLATING_STRUCTS_LINKED_LIST_H
#define PLATING_STRUCTS_LINKED_LIST_H

#include "../utils/MemoryUtils.h"

/**
 * === LinkedListNode<T> ===
 *
 * A container holding a pointer to the element
 * and to the next node.
 */

#define LL_NODE_TYPE(T) LinkedListNode_ ## T
#define LL_NODE_METHOD(T, NAME) LinkedListNode_ ## T ## NAME
#define DECLARE_LL_NODE(T) \
typedef struct LinkedListNode_ ## T {\
	T element;\
	struct LL_NODE_TYPE(T)* next;\
} LinkedListNode_ ## T;\
\
void LL_NODE_METHOD(T, Insert)(LL_NODE_TYPE(T)* node, T element) {\
	LL_NODE_TYPE(T)* newNode = memAlloc(sizeof(LL_NODE_TYPE(T)));\
	newNode->element = element;\
	newNode->next = node->next;\
	node->next = newNode;\
}\
\
void LL_NODE_METHOD(T, Clear)(LL_NODE_TYPE(T)* node) {\
	if (node->next != 0) {\
		LL_NODE_METHOD(T, Clear)(node->next);\
		memFree(node->next);\
	}\
}

/**
 * === LinkedList<T> ===
 *
 * A dynamically growing sequence of elements
 * that is implemented using chaining of the
 * elements.
 */

#define LINKED_LIST_TYPE(T) LinkedList_ ## T
#define LINKED_LIST_METHOD(T, NAME) LinkedList_ ## T ## NAME
#define DECLARE_LINKED_LIST(T) \
\
DECLARE_LL_NODE(T)\
\
typedef struct LinkedList_ ## T {\
	LL_NODE_TYPE(T)* first;\
	LL_NODE_TYPE(T)* last;\
	int length;\
} LinkedList_ ## T;\
\
LINKED_LIST_TYPE(T)* LINKED_LIST_METHOD(T, New)(void) {\
	LINKED_LIST_TYPE(T)* list = memAlloc(sizeof(LINKED_LIST_TYPE(T)));\
	logDeepTrace("Allocated a new LinkedList");\
	list->first = 0;\
	list->length = 0;\
	list->last = 0;\
	return list;\
}\
\
void LINKED_LIST_METHOD(T, Push)(LINKED_LIST_TYPE(T)* list, T element) {\
	if (list->length == 0) {\
		LL_NODE_TYPE(T)* node = memAlloc(sizeof(LL_NODE_TYPE(T)));\
		node->element = element;\
		node->next = 0;\
		\
		list->first = node;\
		list->last = node;\
	} else {\
		LL_NODE_METHOD(T, Insert)(list->last, element);\
		LL_NODE_TYPE(T)* newLast = list->last->next;\
		list->last = newLast;\
	}\
	list->length++;\
}\
\
T LINKED_LIST_METHOD(T, Get)(LINKED_LIST_TYPE(T)* list, int index, T defaultValue) {\
	if ((index < 0) || (index >= list->length)) {\
		logTrace("Linked list index %d out of bounds (length: %d)", index, list->length);\
		return defaultValue;\
	} else {\
		LL_NODE_TYPE(T)* node = list->first;\
		\
		for (int i=0; i<index; i++) {\
			node = node->next;\
		}\
		\
		return node->element;\
	}\
}\
\
void LINKED_LIST_METHOD(T, Delete)(LINKED_LIST_TYPE(T)* list) {\
	if (list->length > 0) {\
		LL_NODE_METHOD(T, Clear)(list->first);\
		memFree(list->first);\
	}\
	memFree(list);\
}

#endif // PLATING_STRUCTS_LINKED_LIST_H