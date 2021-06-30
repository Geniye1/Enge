#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define GL_LOG_FILE  "Logger/Enge_Main.log"

#define ENGE_INFO LogLevel::INFO
#define ENGE_WARNING LogLevel::WARNING
#define ENGE_DEBUG LogLevel::DEBUG

#define LOG_START()  Logger::gl_startGlLog()
#define LOG(flag, ...)     Logger::gl_log(flag, __VA_ARGS__)
#define LOG_ERR(...) Logger::gl_log_err(__VA_ARGS__)

#define CONSOLE_COLOR(colorId) SetConsoleTextAttribute(Logger::consoleHandle, colorId);

enum class LogLevel {
	INFO,
	WARNING,
	DEBUG
};

class Logger {
public:
	static bool gl_startGlLog();
	static bool gl_log(LogLevel flag, const char* message, ...);
	static bool gl_log_err(const char* message, ...);
private:
	static HANDLE consoleHandle;
};

#endif