#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace max {
	Logger g_logger{LogLevel::Info, &std::cout};

	bool Logger::Log(LogLevel loglevel, const std::string filename, int line)
	{
		if (loglevel < m_logLevel) return false;

		switch (loglevel)
		{
		case Info:
			*m_ostream << "INFO: ";
			break;
		case Warning:
			*m_ostream << "WARNING: ";
			break;
		case Error:
			*m_ostream << "ERROR: ";
			break;
		case Assert:
			*m_ostream << "ASSERT: ";
			break;
		default:
			break;
		}

		*m_ostream << getFileName(filename) << "(" << line << ")\n";;

		return true;
	}
}