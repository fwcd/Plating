#ifndef PLATING_STRUCTS_HASH_MAP_H
#define PLATING_STRUCTS_HASH_MAP_H

#include <stdio.h>
#include "../utils/MemoryUtils.h"
#include "../utils/HashFunction.h"
#include "../utils/Logger.h"

/**
 * === Node<K, V> ===
 *
 * A container holding a key-value pair that
 * also works as a linked list. The list
 * is terminated by a null pointer to the next
 * element.
 */

#define NODE_TYPE(K, V) Node_ ## K ## _ ## V
#define NODE_METHOD(K, V, SIGNATURE) Node_ ## K ## _ ## V ## SIGNATURE
#define DECLARE_NODE(K, V) \
typedef struct Node_ ## K ## _ ## V { \
	K key;\
	V value;\
	int empty;\
	struct NODE_TYPE(K, V)* next; /* Each bucket/node references a "next", dynamically allocated bucket/node */\
} Node_ ## K ## _ ## V;\
\
void NODE_METHOD(K, V, Clear)(NODE_TYPE(K, V)* node) {\
	if (node->next != 0) {\
		NODE_METHOD(K, V, Clear)(node->next);\
		logDeepTrace("Deallocating linked node @ %p", node->next);\
		memFree(node->next);\
		node->next = 0;\
	}\
}\

/**
 * === HashMap<K, V> ===
 *
 * An associative array that uses a hashtable to map
 * keys to values. When inserting an element, a custom
 * hash function is used to determine the slot in the
 * array. To deal with hash collisions this implementaion
 * uses a technique referred to as buckets: Every key-value-pair
 * is stored inside a node that also functions as a linked list
 * of key-value-pairs. This linked list contains all nodes
 * that have the same hash value.
 *
 * Access is O(1) if there is no hash collision, otherwise
 * O(n) amongst the "collisions".
 *
 * This implementation is generic and type-safe.
 * An invocation of the declaration macro is required
 * for each specialization. Example:
 *
 * DECLARE_HASH_MAP(int, char)
 */

#define HASH_MAP_TYPE(K, V) HashMap_ ## K ## _ ## V
#define HASH_MAP_METHOD(K, V, SIGNATURE) HashMap_ ## K ## _ ## V ## SIGNATURE
#define DECLARE_HASH_MAP(K, V) \
\
DECLARE_HASH_FUNCTION(K) \
DECLARE_NODE(K, V) \
\
typedef struct HashMap_ ## K ## _ ## V { \
	HashFunction_ ## K hashFunction; \
	NODE_TYPE(K, V)* buckets; /* Buckets are stored as an array */ \
	int bucketCount; \
} HashMap_ ## K ## _ ## V; \
\
HASH_MAP_TYPE(K, V)* HASH_MAP_METHOD(K, V, New)(int bucketCount, HashFunction_ ## K hashFunction) {\
	HASH_MAP_TYPE(K, V)* map = memAlloc(sizeof(HASH_MAP_TYPE(K, V))); \
	logDeepTrace("Allocated a new HashMap"); \
	map->hashFunction = hashFunction; \
	map->bucketCount = bucketCount; \
	map->buckets = memAlloc(bucketCount * sizeof(NODE_TYPE(K, V))); \
	logDeepTrace("Allocated %d HashMap buckets", bucketCount); \
	for (int i=0; i<bucketCount; i++) { \
		NODE_TYPE(K, V)* bucket = &map->buckets[i];\
		bucket->empty = 1;\
		bucket->next = 0;\
		logDeepTrace("Prepared bucket %d of %d @ %p", i, bucketCount, bucket);\
	} \
	logDeepTrace("Prepared HashMap buckets."); \
	return map;\
} \
\
void HASH_MAP_METHOD(K, V, Delete)(HASH_MAP_TYPE(K, V)* map) { \
	int bucketCount = map->bucketCount;\
	for (int i=0; i<bucketCount; i++) {\
		NODE_TYPE(K, V)* node = &map->buckets[i];\
		logDeepTrace("Clearing bucket %d of %d @ %p", i, bucketCount, node);\
		NODE_METHOD(K, V, Clear)(node);\
	}\
	\
	logDeepTrace("Deallocating HashMap buckets");\
	memFree(map->buckets); \
	logDeepTrace("Deallocating HashMap");\
	memFree(map); \
} \
\
void HASH_MAP_METHOD(K, V, Insert)(HASH_MAP_TYPE(K, V)* map, K key, V value) { \
	int index = (map->hashFunction(key)) % (map->bucketCount); \
	NODE_TYPE(K, V)* node = &map->buckets[index];\
	\
	if (node->empty) {\
		node->key = key; \
		node->value = value; \
		node->empty = 0;\
	} else {\
		while (node->next != 0) {\
			node = node->next;\
		}\
		node->next = memAlloc(sizeof(NODE_TYPE(K, V)));\
		NODE_TYPE(K, V)* nextNode = node->next;\
		logDeepTrace("Allocating linked node in HashMap bucket @ %p", nextNode);\
		nextNode->key = key; \
		nextNode->value = value; \
		nextNode->next = 0; \
		nextNode->empty = 0;\
	}\
}\
\
V HASH_MAP_METHOD(K, V, Get)(HASH_MAP_TYPE(K, V)* map, K key, V defaultValue) { \
	int index = (map->hashFunction(key)) % (map->bucketCount); \
	NODE_TYPE(K, V)* node = &map->buckets[index];\
	\
	while (node->key != key) {\
		node = node->next;\
		if (node == 0) {\
			return defaultValue; \
		}\
	}\
	return node->value;\
}

#endif // PLATING_STRUCTS_HASH_MAP_H