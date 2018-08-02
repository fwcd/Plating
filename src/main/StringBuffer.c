#include "plating/StringBuffer.h"
#include "plating/MemoryUtils.h"
#include <string.h>
#include <stdbool.h>

// Private function
StringBuffer* StringBufferAllocate(int initialLength) {
	StringBuffer* instance = memAlloc(sizeof(StringBuffer));
	instance->contents = memAlloc(sizeof(char) * initialLength);
	instance->length = 0;
	instance->allocatedLength = initialLength;
	return instance;
}

StringBuffer* StringBufferNew(void) {
	return StringBufferAllocate(25);
}

StringBuffer* StringBufferFrom(const char* chars) {
	int len = (int) strlen(chars);
	StringBuffer* instance = StringBufferAllocate(len);
	StringBufferReplace(instance, chars);
	return instance;
}

bool StringBufferIndexInBounds(StringBuffer* self, int index) {
	return (index >= 0) && (index < self->length);
}

bool StringBufferIndexInAllocatedBounds(StringBuffer* self, int index) {
	return (index >= 0) && (index < self->allocatedLength);
}

void StringBufferSetChar(StringBuffer* self, int index, char value) {
	if (StringBufferIndexInAllocatedBounds(self, index)) {
		self->contents[index] = value;
	}
}

char StringBufferGetChar(StringBuffer* self, int index) {
	if (StringBufferIndexInBounds(self, index)) {
		return self->contents[index];
	} else {
		return '\0';
	}
}

char StringBufferGetLastChar(StringBuffer* self) {
	return StringBufferGetChar(self, self->length - 1);
}

bool StringBufferIsEmpty(StringBuffer* self) {
	return self->length == 0;
}

bool StringBufferStartsWith(StringBuffer* self, const char* sequence) {
	char compared = sequence[0];
	int i = 0;
	while (compared != '\0') {
		if (i >= self->length) {
			return false;
		}
		if (compared != self->contents[i]) {
			return false;
		}
		i++;
		compared = sequence[i];
	}
	return true;
}

bool StringBufferEndsWith(StringBuffer* self, const char* sequence) {
	int seqLength = (int) strlen(sequence);
	if (seqLength > self->length) {
		return false;
	}
	int startIndex = self->length - seqLength;
	for (int i=0; i<seqLength; i++) {
		if (sequence[i] != self->contents[startIndex + i]) {
			return false;
		}
	}
	return true;
}

char StringBufferPop(StringBuffer* self) {
	if (self->length > 0) {
		int index = self->length - 1;
		char last = self->contents[index];
		self->contents[index] = '\0';
		self->length--;
		return last;
	} else {
		return '\0';
	}
}

// Private function
void StringBufferGrow(StringBuffer* self, int newAllocatedLength) {
	if (self->allocatedLength < newAllocatedLength) {
		char* newContents = memRealloc(self->contents, sizeof(char) * newAllocatedLength);
		self->contents = newContents;
	}
}

void StringBufferPush(StringBuffer* self, char c) {
	StringBufferGrow(self, self->length + 2 /* New char + Null terminator */);
	self->contents[self->length] = c; // Overwrites the current null terminator
	self->contents[self->length + 1] = '\0';
	self->length++;
}

void StringBufferAppend(StringBuffer* self, const char* newContents) {
	int deltaLength = (int) strlen(newContents);
	StringBufferGrow(self, self->length + deltaLength + 1 /* Null terminator*/);
	for (int i=0; i<deltaLength; i++) {
		self->contents[self->length + i] = newContents[i];
	}
	self->contents[self->length + deltaLength] = '\0';
	self->length += deltaLength;
}

void StringBufferAppendBuf(StringBuffer* self, StringBuffer* other) {
	StringBufferAppend(self, other->contents);
}

void StringBufferReplace(StringBuffer* self, const char* newContents) {
	int newLength = (int) strlen(newContents);
	StringBufferGrow(self, newLength + 1 /* Null terminator */);
	for (int i=0; i<newLength; i++) {
		self->contents[i] = newContents[i];
	}
	self->contents[newLength] = '\0';
	self->length = newLength;
}

char* StringBufferGetCopy(StringBuffer* self) {
	char* buf = memAlloc(sizeof(char) * (self->length + 1));
	for (int i=0; i<self->length; i++) {
		buf[i] = StringBufferGetChar(self, i);
	}
	buf[self->length] = '\0';
	return buf;
}

void StringBufferPrint(StringBuffer* self) {
	printf("%s", self->contents);
}

void StringBufferPrintln(StringBuffer* self) {
	printf("%s\n", self->contents);
}

void StringBufferClear(StringBuffer* self) {
	self->length = 0;
}

void StringBufferDelete(StringBuffer* self) {
	memFree(self->contents);
	memFree(self);
}
