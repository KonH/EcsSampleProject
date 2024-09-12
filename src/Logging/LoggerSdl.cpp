#ifdef USE_LOG_SDL
#include "Logger.h"

#include <SDL.h>

namespace Sample::Logging {
	void Logger::LogInfoImpl(const std::string& message) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
	}

	void Logger::LogWarningImpl(const std::string& message) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
	}

	void Logger::LogErrorImpl(const std::string& message) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
	}
}
#endif