#include "Logger.h"

bool Logger::gl_startGlLog() {
	
	FILE* logFile;
	errno_t errId = fopen_s(&logFile, GL_LOG_FILE, "w+");
	if (errId || logFile == NULL) {
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for writing dumbass\n",
			GL_LOG_FILE);
		return false;
	}
	
	time_t now = time(NULL);
	char date[26];
	ctime_s(date, sizeof(date), &now);
	fprintf(logFile, "GL_LOG_FILE ### local time %s\n", date);
	fclose(logFile);
	
	return true;
}

bool Logger::gl_log(char flag, const char* message, ...) {
	
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
	case 'i':
		fprintf(logFile, "LOG INFO %s ### ", date);
		break;
	case 'w':
		fprintf(logFile, "LOG WARNING %s ### ", date);
		break;
	case 'd':
		fprintf(logFile, "LOG DEBUG %s ### ", date);
		break;
	default:
		fprintf(stderr,
			"ERROR: Logger GL_LOG_FILE %s was supplied an unknown flag, fix it you buffon, huh yeah big dumb man dumb dumb man yeah? yeah? big stupid very cringe",
			GL_LOG_FILE);
		return false;
	}

	va_start(argListPtr, message); // Begin fetching the additional arguments
	vfprintf(logFile, message, argListPtr);
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

	fprintf(logFile, "LOG ERROR %s ### ", date);

	va_start(argListPtr, message); // Begin fetching the additional arguments
	vfprintf(logFile, message, argListPtr);
	va_end(argListPtr); // Finish fetching the additional arguments
	va_start(argListPtr, message); 
	vfprintf(stderr, message, argListPtr); // Print out the stderr as well
	va_end(argListPtr);
	fclose(logFile);
	free(date);
	return true;
}