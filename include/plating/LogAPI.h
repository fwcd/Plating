#ifndef PLATING_LOG_API_H
#define PLATING_LOG_API_H

/**
 * This file contains a convenient wrapper
 * around the Logging API. To use it, set 'platingLogLevel'
 * to your log level somewhere visible to the linker.
 */

extern int platingLogLevel;

void logMessage(int level, const char* prefix, const char* msg, ...);

void logError(const char* msg, ...);

void logWarn(const char* msg, ...);

void logInfo(const char* msg, ...);

void logDebug(const char* msg, ...);

void logTrace(const char* msg, ...);

void logDeepTrace(const char* msg, ...);

#endif // PLATING_LOG_API_H
