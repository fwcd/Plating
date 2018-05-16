#ifndef PLATING_STRUCTS_HASH_MAP_H
#define PLATING_STRUCTS_HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "../utils/HashFunction.h"

#define NODE_TYPE(K, V) Node_ ## K ## _ ## V
#define DECLARE_NODE(K, V) \
typedef struct Node_ ## K ## _ ## V { \
	K key;\
	V value;\
	int empty;\
	struct NODE_TYPE(K, V)* next;\
} Node_ ## K ## _ ## V;

#define HASH_MAP_TYPE(K, V) HashMap_ ## K ## _ ## V
#define HASH_MAP_METHOD(K, V, SIGNATURE) HashMap_ ## K ## _ ## V ## SIGNATURE
#define DECLARE_HASH_MAP(K, V) \
\
DECLARE_HASH_FUNCTION(K) \
DECLARE_NODE(K, V) \
\
typedef struct HashMap_ ## K ## _ ## V { \
	HashFunction_ ## K hashFunction; \
	NODE_TYPE(K, V)** buckets; \
	int bucketCount; \
} HashMap_ ## K ## _ ## V; \
\
HASH_MAP_TYPE(K, V)* HASH_MAP_METHOD(K, V, New(int bucketCount, HashFunction_ ## K hashFunction)) {\
	HASH_MAP_TYPE(K, V)* map = malloc(sizeof(HASH_MAP_TYPE(K, V))); \
	map->hashFunction = hashFunction; \
	map->bucketCount = bucketCount; \
	map->buckets = malloc(bucketCount * sizeof(HASH_MAP_TYPE(K, V))); \
	for (int i=0; i<bucketCount; i++) { \
		NODE_TYPE(K, V)* bucket = map->buckets[i];\
		bucket->empty = 1;\
		bucket->next = 0;\
	} \
	return map;\
} \
\
void HASH_MAP_METHOD(K, V, Delete(HASH_MAP_TYPE(K, V)* map)) { \
	int bucketCount = map->bucketCount;\
	for (int i=0; i<bucketCount; i++) {\
		NODE_TYPE(K, V)* node = map->buckets[i];\
		NODE_TYPE(K, V)* nextNode = 0;\
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
void HASH_MAP_METHOD(K, V, Insert(HASH_MAP_TYPE(K, V)* map, K key, V value)) { \
	int index = (map->hashFunction(key)) % (map->bucketCount); \
	NODE_TYPE(K, V)* node = map->buckets[index];\
	\
	if (node->empty) {\
		node->key = key; \
		node->value = value; \
		node->empty = 0;\
	} else {\
		while (node->next != 0) {\
			node = node->next;\
		}\
		node->next = malloc(sizeof(NODE_TYPE(K, V)));\
		node->next->key = key; \
		node->next->value = value; \
		node->next->next = 0; \
		node->next->empty = 0;\
	}\
}\
\
V HASH_MAP_METHOD(K, V, Get(HASH_MAP_TYPE(K, V)* map, K key, V defaultValue)) { \
	int index = (map->hashFunction(key)) % (map->bucketCount); \
	NODE_TYPE(K, V)* node = map->buckets[index];\
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