#ifndef PLATING_FILE_READER_H
#define PLATING_FILE_READER_H

#include <stdio.h>
#include <stdbool.h>
#include "StringBuffer.h"

/**
 * Reads the next line from the file into
 * the provided buffer WITHOUT its trailing
 * newline. The buffer's contents are replaced.
 * 
 * Returns whether the line could be read successfully.
 * (Thus returning false when the file has ended)
 */
bool readLineFromFile(FILE* fileStream, StringBuffer* buffer);

#endif // PLATING_FILE_READER_H
