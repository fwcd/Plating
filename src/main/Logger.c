#include "plating/Logger.h"
#include "plating/LogLevels.h"

void logMessageWithLevel(int currentLevel, int level, const char* prefix, const char* msg, va_list args) {
	if (currentLevel <= level) {
		printf("%s", prefix);
		vprintf(msg, args);
		printf("\n");
	}
}

void logErrorWithLevel(int currentLevel, const char* msg, va_list args) {
	logMessageWithLevel(currentLevel, LOG_LEVEL_ERROR, "[ERROR]   ", msg, args);
}

void logWarnWithLevel(int currentLevel, const char* msg, va_list args) {
	logMessageWithLevel(currentLevel, LOG_LEVEL_WARN, "[WARN]    ", msg, args);
}

void logInfoWithLevel(int currentLevel, const char* msg, va_list args) {
	logMessageWithLevel(currentLevel, LOG_LEVEL_INFO, "[INFO]    ", msg, args);
}

void logDebugWithLevel(int currentLevel, const char* msg, va_list args) {
	logMessageWithLevel(currentLevel, LOG_LEVEL_DEBUG, "[DEBUG]   ", msg, args);
}

void logTraceWithLevel(int currentLevel, const char* msg, va_list args) {
	logMessageWithLevel(currentLevel, LOG_LEVEL_TRACE, "[TRACE]   ", msg, args);
}

void logDeepTraceWithLevel(int currentLevel, const char* msg, va_list args) {
	logMessageWithLevel(currentLevel, LOG_LEVEL_DEEP_TRACE, "[D_TRACE] ", msg, args);
}
