#include "plating/PathUtils.h"

char pathSeparator(void) {
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif
}

void ensureEndsWithPathSeparator(StringBuffer* path) {
	char separator = pathSeparator();
	if (StringBufferGetChar(path, path->length - 1) != separator) {
		StringBufferPush(path, separator);
	}
}

void pathAppend(StringBuffer* left, const char* right) {
	ensureEndsWithPathSeparator(left);
	StringBufferAppend(left, right);
}
