#pragma once

#include "bcppul_expimp.h"

#include <string>
#include <iostream>
#include <fstream>

namespace bcppul {
	BCPPUL_API class Logger;
	BCPPUL_API Logger* getLogger(std::string name, Logger* parent = nullptr);

	BCPPUL_API enum LogLevel {
		TRACE,
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL,
		NONE
	};
	extern BCPPUL_API std::string log_levels_s[LogLevel::NONE + 1];
	extern BCPPUL_API Logger* logger_root;
	extern BCPPUL_API LogLevel console_log_level;
	extern BCPPUL_API LogLevel file_log_level;
	extern BCPPUL_API std::string logOutFileName;
	extern BCPPUL_API std::ofstream logOutFS;

	BCPPUL_API struct LogRecord {
		Logger* logger;
		LogLevel level;
		const char* message;

		friend std::ostream& operator<<(std::ostream& os, LogRecord& logRecord);
	};
	BCPPUL_API class Logger {
	private:
	protected:
		std::string name;
		Logger(std::string name, Logger* parent = logger_root);
	public:
		std::string getName();
		void setName(std::string name);

		void BCPPUL_API log(LogRecord& record);
		void BCPPUL_API log(LogLevel level, const char* message);
		void BCPPUL_API trace(const char* message);
		void BCPPUL_API debug(const char* message);
		void BCPPUL_API info(const char* message);
		void BCPPUL_API warning(const char* message);
		void BCPPUL_API error(const char* message);
		void BCPPUL_API fatal(const char* message);

		friend BCPPUL_API Logger* getLogger(std::string name, Logger* parent);
	};

	BCPPUL_API void initLogging();
	BCPPUL_API void finalizationLogging();

	BCPPUL_API void logLogRecord(LogRecord& record);
}