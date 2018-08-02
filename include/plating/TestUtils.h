#ifndef PLATING_TEST_UTILS_H
#define PLATING_TEST_UTILS_H

#include "StringBuffer.h"
#include <stdbool.h>

void assertTrue(bool cond, const char* msg);

void assertFalse(bool cond, const char* msg);

void assertIntEq(int expected, int actual);

void assertPtrEq(void* expected, void* actual);

void assertStrEq(const char* expected, const char* actual);

void assertStringBufferEq(const char* expected, StringBuffer* actual);

void assertLeaks(int leaks);

void fail(void);

void pass(const char* name);

#endif // PLATING_TEST_UTILS_H
