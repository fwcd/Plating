#include "plating/FileReader.h"
#include "plating/LogAPI.h"
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER_SIZE 100

bool readLineFromFile(FILE* fileStream, StringBuffer* buffer) {
	StringBufferClear(buffer);
	char segment[LINE_BUFFER_SIZE];
	do {
		if (fgets(segment, LINE_BUFFER_SIZE, fileStream) == NULL) {
			if (ferror(fileStream)) {
				logError("Error while reading file");
			}
			return false;
		} else {
			// Read successfully to segment
			StringBufferAppend(buffer, segment);
		}
	} while (strchr(segment, '\n') == NULL);
	if (StringBufferGetLastChar(buffer) == '\n') {
		StringBufferPop(buffer);
	}
	return true;
}
