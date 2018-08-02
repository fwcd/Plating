#ifndef PLATING_PATH_UTILS_H
#define PLATING_PATH_UTILS_H

#include "StringBuffer.h"

char pathSeparator(void);

void pathAppend(StringBuffer* left, const char* right);

#endif // PLATING_PATH_UTILS_H
