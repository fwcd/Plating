#ifndef PLATING_LOG_API_H
#define PLATING_LOG_API_H

#include <stdarg.h>
#include "Logger.h"

/**
 * This file contains a convenient wrapper
 * around the Logging API. To use it, implement
 * this header by declaring 'platingLogLevel'
 * somewhere visible to the linker.
 */

extern int platingLogLevel;

#define LOG_FUNCTION_BODY(IMPL_FUNC_CALL)\
	va_list args;\
	va_start(args, msg);\
	IMPL_FUNC_CALL;\
	va_end(args);

void logMessage(int level, const char* prefix, const char* msg, ...) {
	LOG_FUNCTION_BODY(logMessageWithLevel(platingLogLevel, level, prefix, msg, args))
}

void logError(const char* msg, ...) {
	LOG_FUNCTION_BODY(logErrorWithLevel(platingLogLevel, msg, args))
}

void logWarn(const char* msg, ...) {
	LOG_FUNCTION_BODY(logWarnWithLevel(platingLogLevel, msg, args))
}

void logInfo(const char* msg, ...) {
	LOG_FUNCTION_BODY(logInfoWithLevel(platingLogLevel, msg, args))
}

void logDebug(const char* msg, ...) {
	LOG_FUNCTION_BODY(logDebugWithLevel(platingLogLevel, msg, args))
}

void logTrace(const char* msg, ...) {
	LOG_FUNCTION_BODY(logTraceWithLevel(platingLogLevel, msg, args))
}

void logDeepTrace(const char* msg, ...) {
	LOG_FUNCTION_BODY(logDeepTraceWithLevel(platingLogLevel, msg, args))
}

#endif // PLATING_LOG_API_H
