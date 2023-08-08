#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace max {
	Logger g_logger{LogLevel::Info, &std::cout, "log.txt"};

	bool Logger::Log(LogLevel loglevel, const std::string filename, int line)
	{
		if (loglevel < m_logLevel) return false;

		switch (loglevel)
		{
		case Info:
			*this << "INFO: ";
			break;
		case Warning:
			*this << "WARNING: ";
			break;
		case Error:
			*this << "ERROR: ";
			break;
		case Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";;

		return true;
	}
}