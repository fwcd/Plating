#ifndef PLATING_LOGGER_H
#define PLATING_LOGGER_H

#include <stdarg.h>

void logMessageWithLevel(int currentLevel, int level, const char* prefix, const char* msg, va_list args);

void logErrorWithLevel(int currentLevel, const char* msg, va_list args);

void logWarnWithLevel(int currentLevel, const char* msg, va_list args);

void logInfoWithLevel(int currentLevel, const char* msg, va_list args);

void logDebugWithLevel(int currentLevel, const char* msg, va_list args);

void logTraceWithLevel(int currentLevel, const char* msg, va_list args);

void logDeepTraceWithLevel(int currentLevel, const char* msg, va_list args);

#endif // PLATING_LOGGER_H
