#pragma once
#include <iostream>
#include <vulkan/vulkan.h>
#include <assert.h>

typedef enum LogLevel {
    ERROR = 0x00000001,
    WARN = 0x00000002,
    INFO = 0x00000004,
    DEBUG = 0x00000008,
    TRACE = 0x00000010
} LogLevel;

#ifdef ERROR_LOG_LEVEL
#define CURRENT_LOG_LEVEL ERROR
#endif

#ifdef WARN_LOG_LEVEL
#define CURRENT_LOG_LEVEL WARN
#endif

#ifdef INFO_LOG_LEVEL
#define CURRENT_LOG_LEVEL INFO
#endif

#ifdef DEBUG_LOG_LEVEL
#define CURRENT_LOG_LEVEL DEBUG
#endif

#ifdef TRACE_LOG_LEVEL
#define CURRENT_LOG_LEVEL TRACE
#endif

#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL ERROR
#endif

void errorCheck(VkResult result);
void logMessage(LogLevel logLevel, const char *msg);