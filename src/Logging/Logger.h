#pragma once

#include <string>
#include <fmt/core.h>

namespace Sample::Logging {
	class Logger {
	public:
		template<typename... Args>
		static void LogInfo(const std::string& format, Args&&... args) {
			LogInfoImpl(formatMessage(format, std::forward<Args>(args)...));
		}

		static void LogInfoImpl(const std::string& message);

		template<typename... Args>
		static void LogWarning(const std::string& format, Args&&... args) {
			LogWarningImpl(formatMessage(format, std::forward<Args>(args)...));
		}

		static void LogWarningImpl(const std::string& message);

		template<typename... Args>
		static void LogError(const std::string& format, Args&&... args) {
			LogErrorImpl(formatMessage(format, std::forward<Args>(args)...));
		}

		static void LogErrorImpl(const std::string& message);

		template<typename... Args>
		static std::string formatMessage(const std::string& format, Args&&... args) {
			return fmt::format(fmt::runtime(format), std::forward<Args>(args)...);
		}
	};
}