#ifndef PLATING_UTILS_LOGGER_H
#define PLATING_UTILS_LOGGER_H

#ifndef LOG_LEVEL
#error "No LOG_LEVEL defined"
#endif

#include <stdarg.h>
#include <stdio.h>
#include "LogLevels.h"

#define LOG_FUNCTION(PREFIX, LEVEL, MSG) \
	va_list args;\
	va_start(args, MSG);\
	logMessage(LOG_LEVEL_ ## LEVEL, PREFIX, MSG, args);\
	va_end(args);

void logMessage(int level, const char* prefix, const char* msg, va_list args) {
	if (LOG_LEVEL <= level) {
		printf("%s", prefix);
		vprintf(msg, args);
		printf("\n");
	}
}

void logError(const char* msg, ...) {
#if LOG_LEVEL <= LOG_LEVEL_ERROR
	LOG_FUNCTION("[ERROR]   ", ERROR, msg)
#endif
}

void logWarn(const char* msg, ...) {
#if LOG_LEVEL <= LOG_LEVEL_WARN
	LOG_FUNCTION("[WARN]    ", WARN, msg)
#endif
}

void logInfo(const char* msg, ...) {
#if LOG_LEVEL <= LOG_LEVEL_INFO
	LOG_FUNCTION("[INFO]    ", INFO, msg)
#endif
}

void logDebug(const char* msg, ...) {
#if LOG_LEVEL <= LOG_LEVEL_DEBUG
	LOG_FUNCTION("[DEBUG]   ", DEBUG, msg)
#endif
}

void logTrace(const char* msg, ...) {
#if LOG_LEVEL <= LOG_LEVEL_TRACE
	LOG_FUNCTION("[TRACE]   ", TRACE, msg)
#endif
}

void logDeepTrace(const char* msg, ...) {
#if LOG_LEVEL <= LOG_LEVEL_DEEP_TRACE
	LOG_FUNCTION("[D_TRACE] ", TRACE, msg)
#endif
}

#endif // PLATING_UTILS_LOGGER_H
