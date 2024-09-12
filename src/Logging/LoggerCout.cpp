#ifdef USE_LOG_COUT
#include "Logger.h"

#include <iostream>

namespace Sample::Logging {
	void Logger::LogInfoImpl(const std::string& message) {
		std::cout << "[INFO] " << message << std::endl;
	}

	void Logger::LogWarningImpl(const std::string& message) {
		std::cout << "[WARNING] " << message << std::endl;
	}

	void Logger::LogErrorImpl(const std::string& message) {
		std::cerr << "[ERROR] " << message << std::endl;
	}
};
#endif