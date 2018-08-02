#ifndef PLATING_FILE_READER_TEST_H
#define PLATING_FILE_READER_TEST_H

#include "plating/TestUtils.h"
#include "plating/StringBuffer.h"
#include "plating/PathUtils.h"
#include "plating/FileReader.h"
#include <stdio.h>

void testFileReader(const char* testResourcesFolder) {
	StringBuffer* testFilePathBuf = StringBufferFrom(testResourcesFolder);
	pathAppend(testFilePathBuf, "testfile.txt");
	char* testFilePath = StringBufferGetCopy(testFilePathBuf);
	FILE* file = fopen(testFilePath, "r");
	StringBuffer* lineBuf = StringBufferNew();
	
	readLineFromFile(file, lineBuf);
	assertStringBufferEq("A file that is intended for testing.", lineBuf);
	readLineFromFile(file, lineBuf);
	assertStringBufferEq("This line is intentionally longer than 100 characters to test whether the buffer reallocates correctly.", lineBuf);
	readLineFromFile(file, lineBuf);
	assertStringBufferEq("Empty lines are used too.", lineBuf);
	readLineFromFile(file, lineBuf);
	assertStringBufferEq("", lineBuf);
	readLineFromFile(file, lineBuf);
	assertStringBufferEq("", lineBuf);
	assertFalse(readLineFromFile(file, lineBuf), "readLineFromFile should return false upon EOF");
	
	fclose(file);
	memFree(testFilePath);
	StringBufferDelete(lineBuf);
	StringBufferDelete(testFilePathBuf);
	assertLeaks(0);
	pass("FileReader");
}

#endif // PLATING_FILE_READER_TEST_H
