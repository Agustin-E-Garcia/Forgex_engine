#include "Log.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Forgex::Debug
{
	const std::string Log::s_CoreLogger = "CORE";
	const std::string Log::s_ClientLogger = "APPLICATION";
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		spdlog::stderr_color_mt(s_CoreLogger)->set_level(spdlog::level::trace);
		LOG_CORE(LogLevel::Info , "Logger {0} initialized", s_CoreLogger);
		
		spdlog::stderr_color_mt(s_ClientLogger)->set_level(spdlog::level::trace);
		LOG_CORE(LogLevel::Info , "Logger {0} initialized", s_ClientLogger);
	}

	void Log::LogMessage(std::string loggerID, LogLevel level, const std::string& message)
	{
		auto logger = spdlog::get(loggerID);
		if(!logger) return;

		switch(level)
		{
		case Trace:
			logger->trace(message);
			break;
		case Info:
			logger->info(message);
			break;
		case Warning:
			logger->warn(message);
			break;
		case Error:
			logger->error(message);
			break;
		case Critical:
			logger->critical(message);
			break;
		}
	}
}