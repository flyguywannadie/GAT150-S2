#pragma once
#include <string>
#include <fstream>
#include <cassert>

#define INFO_LOG { max::g_logger.Log(max::LogLevel::Info, __FILE__, __LINE__); }
#define WARNING_LOG { max::g_logger.Log(max::LogLevel::Warning, __FILE__, __LINE__); }
#define ERROR_LOG { max::g_logger.Log(max::LogLevel::Error, __FILE__, __LINE__); }
#define ASSERT_LOG { max::g_logger.Log(max::LogLevel::Assert, __FILE__, __LINE__); }

namespace max {
	enum LogLevel {
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger {
	public:
		Logger(LogLevel loglevel, std::ostream* ostream) : m_logLevel{ loglevel }, m_ostream{ ostream } {};

		bool Log(LogLevel loglevel, const std::string filename, int line);


	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;
}