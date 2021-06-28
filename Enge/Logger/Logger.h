#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GL_LOG_FILE  "Logger/Enge_Main.log"

#define LOG_START()  Logger::gl_startGlLog()
#define LOG(...)     Logger::gl_log(__VA_ARGS__)
#define LOG_ERR(...) Logger::gl_log_err(__VA_ARGS__)

class Logger {
public:
	
	static bool gl_startGlLog();
	static bool gl_log(const char* message, ...);
	static bool gl_log_err(const char* message, ...);

};

#endif