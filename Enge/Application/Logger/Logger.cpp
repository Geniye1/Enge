#include "Logger.h"

// Because static members exist outside the class, you have to initialize the variable
// here and not in the function
void* Logger::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

bool Logger::gl_startGlLog() {
	
	FILE* logFile;
	errno_t errId = fopen_s(&logFile, GL_LOG_FILE, "w+");
	if (errId || logFile == NULL) {
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for writing dumbass\n",
			GL_LOG_FILE);
		return false;
	}

	CONSOLE_COLOR(15);
	

	time_t now = time(NULL);
	char date[26];
	ctime_s(date, sizeof(date), &now);
	fprintf(logFile, "GL_LOG_FILE ### local time %s\n", date); // Print to Log file
	fprintf(stdout, "GL_LOG_FILE ### local time %s\n", date);  // Print to stdout
	fclose(logFile);
	
	return true;
}

bool Logger::gl_log(LogLevel flag, const char* message, ...) {
	
	// Pointer used to access any extra parameters that are passed in the ...
	va_list argListPtr;

	FILE* logFile;
	errno_t errId = fopen_s(&logFile, GL_LOG_FILE, "a");
	if (errId || logFile == NULL) {
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for appending dumbass\n",
			GL_LOG_FILE);
		return false;
	}
	
	time_t now = time(NULL);
	char date[26];
	ctime_s(date, sizeof(date), &now);

	switch (flag) {
	case LogLevel::INFO:
		CONSOLE_COLOR(10);
		fprintf(logFile, "LOG INFO %s ### ", date);
		fprintf(stdout, "LOG INFO %s ### ", date);
		break;
	case LogLevel::WARNING:
		CONSOLE_COLOR(14);
		fprintf(logFile, "LOG WARNING %s ### ", date);
		fprintf(stdout, "LOG WARNING %s ### ", date);
		break;
	case LogLevel::DEBUG:
		CONSOLE_COLOR(13);
		fprintf(logFile, "LOG DEBUG %s ### ", date);
		fprintf(stdout, "LOG DEBUG %s ### ", date);
		break;
	default:
		CONSOLE_COLOR(12);
		fprintf(stderr,
			"ERROR: Logger GL_LOG_FILE %s was supplied an unknown flag, fix it you buffoon, huh yeah big dumb man dumb dumb man yeah? yeah? big stupid very cringe",
			GL_LOG_FILE);
		return false;
	}

	va_start(argListPtr, message); // Begin fetching the additional arguments
	vfprintf(logFile, message, argListPtr);
	vfprintf(stdout, message, argListPtr);
	va_end(argListPtr); // Finish fetching the additional arguments
	fclose(logFile);
	
	return true;
}

bool Logger::gl_log_err(const char* message, ...) {
	// Pointer used to access any extra parameters that are passed in the ...
	va_list argListPtr;

	FILE* logFile;
	errno_t errId = fopen_s(&logFile, GL_LOG_FILE, "a");
	if (errId || logFile == NULL) {
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for appending dumbass\n",
			GL_LOG_FILE);
		return false;
	}

	time_t now = time(NULL);
	char date[26];
	ctime_s(date, sizeof(date), &now);

	CONSOLE_COLOR(12);

	fprintf(logFile, "LOG ERROR %s ### ", date);
	fprintf(stderr, "LOG ERROR %s ### ", date);

	va_start(argListPtr, message); // Begin fetching the additional arguments
	vfprintf(logFile, message, argListPtr);
	va_end(argListPtr); // Finish fetching the additional arguments
	va_start(argListPtr, message); 
	vfprintf(stderr, message, argListPtr); // Print out the stderr as well
	va_end(argListPtr);
	fclose(logFile);

	return true;
}