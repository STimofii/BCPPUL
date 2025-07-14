#include "bcppul/logging.h"

#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>
#include <sstream>

namespace bcppul {
	std::string log_levels_s[LogLevel::NONE + 1] = {
	"TRACE",
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR",
	"FATAL",
	"NONE"
	};

	std::unordered_map<std::string, Logger*> loggers;
	Logger* logger_root = getLogger(std::string(""));
	LogLevel console_log_level = LogLevel::TRACE;
	LogLevel file_log_level = LogLevel::WARNING;
	std::string logOutFileName = "log.log";
	std::ofstream logOutFS;
	std::mutex mutex;

	Logger::Logger(std::string name, Logger* parent)
	{
		if (parent != nullptr) {
			this->name = parent->getName() + "/";
		}
		this->name += name;
	}
	std::string Logger::getName()
	{
		return name;
	}
	void Logger::setName(std::string name)
	{
		this->name = name;
	}
	void Logger::log(LogRecord& record)
	{
		logLogRecord(record);
	}
	void Logger::log(LogLevel level, const char* message)
	{
		logLogRecord(LogRecord{this, level, message});
	}
	void Logger::trace(const char* message)
	{
		log(TRACE, message);
	}
	void Logger::debug(const char* message)
	{
		log(DEBUG, message);
	}
	void Logger::info(const char* message)
	{
		log(INFO, message);
	}
	void Logger::warning(const char* message)
	{
		log(WARNING, message);
	}
	void Logger::error(const char* message)
	{
		log(ERROR, message);
	}
	void Logger::fatal(const char* message)
	{
		log(FATAL, message);
	}
	std::ostream& operator<<(std::ostream& os, LogRecord& logRecord)
	{
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* ptm = std::localtime(&now_c);
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
		os		<< std::setfill('0') << std::setw(2) << ptm->tm_mday << "."
				<< std::setfill('0') << std::setw(2) << (ptm->tm_mon + 1) << "."
				<< (ptm->tm_year + 1900) << " "
				<< std::setfill('0') << std::setw(2) << ptm->tm_hour << ":"
				<< std::setfill('0') << std::setw(2) << ptm->tm_min << ":"
				<< std::setfill('0') << std::setw(2) << ptm->tm_sec << "."
				<< std::setfill('0') << std::setw(3) << milliseconds.count()
				<< " [" << logRecord.logger->getName() << "][" << std::this_thread::get_id() << "]["
				<< log_levels_s[logRecord.level] << "] " << logRecord.message << std::endl;
		return os;
	}
	Logger* getLogger(std::string name, Logger* parent)
	{
		static std::unordered_map<std::string, Logger*> loggers;
		std::string full_name;

		if(parent != nullptr){
			full_name = parent->getName() + "/";
		}
		full_name += name;
		if (loggers.find(full_name) == loggers.end()) {
			loggers[full_name] = new Logger(name, parent);
		}
		return loggers[full_name];
	}
	void initLogging()
	{
		if(file_log_level != NONE){
			logOutFS.open(logOutFileName);
		}
	}
	void finalizationLogging()
	{
		logOutFS.close();
		for (auto& pair : loggers) {
			delete pair.second;
		}
		loggers.clear();
	}
	void logLogRecord(LogRecord& record)
	{
		mutex.lock();
		if (record.level >= console_log_level) {
			if(record.level >= LogLevel::WARNING){
				std::cerr << record;
			}
			else {
				std::cout << record;
			}
		}
		if (record.level >= file_log_level) {
			logOutFS << record;
		}
		mutex.unlock();
	}
	LogStream::LogStream(Logger* logger, LogLevel level) : logger_ptr(logger), current_level(level)
	{

	}
	LogStream::~LogStream()
	{
		{
			if (logger_ptr) {
				logger_ptr->log(current_level, message_stream.str());
			}
		}
	}
}