#ifndef PLATING_STRING_BUFFER_H
#define PLATING_STRING_BUFFER_H

#include <stdbool.h>

/**
 * A mutable, dynamically growing sequence of characters.
 */
typedef struct {
	char* contents;
	// The "actual" length of the string WITHOUT the null terminator
	int length;
	// The allocated length WITH the null terminator
	int allocatedLength;
} StringBuffer;

/** Allocates a new StringBuffer of size 25 */
StringBuffer* StringBufferNew(void);

/** Creates a new StringBuffer from the provided characters */
StringBuffer* StringBufferFrom(const char* chars);

/** 
 * Sets the character at the provided index.
 * Does nothing if the index is outside of the allocated bounds.
 */
void StringBufferSetChar(StringBuffer* self, int index, char value);

/** 
 * Fetches the character at the provided index.
 * Returns '\0' when the index is out of bounds.
 */
char StringBufferGetChar(StringBuffer* self, int index);

/**
 * Fetches the last character of this StringBuffer
 * or '\0' if it is empty.
 */
char StringBufferGetLastChar(StringBuffer* self);

/** Checks whether this StringBuffer is empty */
bool StringBufferIsEmpty(StringBuffer* self);

/** Checks whether this StringBuffer starts with the provided sequence */
bool StringBufferStartsWith(StringBuffer* self, const char* sequence);

/** Checks whether this StringBuffer ends with the provided sequence */
bool StringBufferEndsWith(StringBuffer* self, const char* sequence);

/** Prints this StringBuffer to stdout */
void StringBufferPrint(StringBuffer* self);

/** Prints as this StringBuffer plus a newline to stdout */
void StringBufferPrintln(StringBuffer* self);

/** 
 * Removes and returns the last character of this StringBuffer.
 * Returns '\0' if the StringBuffer is empty.
 */
char StringBufferPop(StringBuffer* self);

/** Appends a character to the StringBuffer */
void StringBufferPush(StringBuffer* self, char c);

/** Appends the contents of another StringBuffer to this */
void StringBufferAppendBuf(StringBuffer* self, StringBuffer* other);

/** Appends a sequence of characters to the StringBuffer */
void StringBufferAppend(StringBuffer* self, const char* newContents);

/** Replaces the StringBuffer's contents with the provided string */
void StringBufferReplace(StringBuffer* self, const char* newContents);

/**
 * Returns a dynamically allocated copy
 * of this StringBuffer's contents.
 * 
 * The caller takes the responsibility to free
 * the result himself.
 */
char* StringBufferGetCopy(StringBuffer* self);

/** Clears the StringBuffer's contents */
void StringBufferClear(StringBuffer* self);

/** Frees this StringBuffer and it's contents */
void StringBufferDelete(StringBuffer* self);

#endif // PLATING_STRING_BUFFER_H
