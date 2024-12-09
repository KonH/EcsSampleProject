#pragma once

#include <string>
#include <format>

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
		static std::string formatMessage(const std::string &format, Args &&...args) {
			try {
				return std::vformat(format, std::make_format_args(args...));
			} catch (const std::format_error &e) {
				return std::string("Formatting error: ") + e.what();
			}
		}
	};
}