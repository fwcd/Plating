#ifndef PLATING_STRUCTS_HASH_MAP_H
#define PLATING_STRUCTS_HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "../utils/HashFunction.h"

#define DECLARE_NODE(K, V) \
typedef struct Node_ ## K ## _ ## V { \
	K key;\
	V value;\
	int empty;\
	struct Node_ ## K ## _ ## V* next;\
} Node_ ## K ## _ ## V;

#define DECLARE_HASH_MAP(K, V) \
\
DECLARE_HASH_FUNCTION(K) \
DECLARE_NODE(K, V) \
\
typedef struct HashMap_ ## K ## _ ## V { \
	HashFunction_ ## K hashFunction; \
	Node_ ## K ## _ ## V** buckets; \
	int bucketCount; \
} HashMap_ ## K ## _ ## V; \
\
HashMap_ ## K ## _ ## V* HashMap_ ## K ## _ ## V ## New(int bucketCount, HashFunction_ ## K hashFunction) {\
	HashMap_ ## K ## _ ## V* map = malloc(sizeof(HashMap_ ## K ## _ ## V)); \
	map->hashFunction = hashFunction; \
	map->bucketCount = bucketCount; \
	map->buckets = malloc(bucketCount * sizeof(HashMap_ ## K ## _ ## V)); \
	for (int i=0; i<bucketCount; i++) { \
		Node_ ## K ## _ ## V* bucket = map->buckets[i];\
		bucket->empty = 1;\
		bucket->next = 0;\
	} \
	return map;\
} \
\
void HashMap_ ## K ## _ ## V ## Delete(HashMap_ ## K ## _ ## V* map) { \
	int bucketCount = map->bucketCount;\
	for (int i=0; i<bucketCount; i++) {\
		Node_ ## K ## _ ## V* node = map->buckets[i];\
		Node_ ## K ## _ ## V* nextNode = 0;\
		if (node != 0) {\
			do {\
				nextNode = node->next;\
				free(node);\
				node = nextNode;\
			} while (node != 0);\
		}\
	}\
	\
	free(map->buckets); \
	free(map); \
} \
\
void HashMap_ ## K ## _ ## V ## Insert(HashMap_ ## K ## _ ## V* map, K key, V value) { \
	int index = (map->hashFunction(key)) % (map->bucketCount); \
	Node_ ## K ## _ ## V* node = map->buckets[index];\
	\
	if (node->empty) {\
		node->key = key; \
		node->value = value; \
		node->empty = 0;\
	} else {\
		while (node->next != 0) {\
			node = node->next;\
		}\
		node->next = malloc(sizeof(Node_ ## K ## _ ## V));\
		node->next->key = key; \
		node->next->value = value; \
		node->next->next = 0; \
		node->next->empty = 0;\
	}\
}\
\
V HashMap_ ## K ## _ ## V ## Get(HashMap_ ## K ## _ ## V* map, K key, V defaultValue) { \
	int index = (map->hashFunction(key)) % (map->bucketCount); \
	Node_ ## K ## _ ## V* node = map->buckets[index];\
	\
	if (node == 0) {\
		return defaultValue; \
	} else {\
		while (node->key != key) {\
			node = node->next;\
			if (node == 0) {\
				return defaultValue; \
			}\
		}\
		return node->value;\
	}\
}

#endif