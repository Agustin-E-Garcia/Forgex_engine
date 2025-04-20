#pragma once
#include "..\DebugExports.h"
#include <string>
#include <format>

namespace Forgex::Debug
{
	enum LogLevel
	{
		Trace,
		Info,
		Warning,
		Error,
		Critical
	};
	
	class DEBUG_API Log
	{
	public:
		static void Init();

		template<typename... Args>
		static void CoreLog(LogLevel level, std::string_view fmt, Args&&... args)
		{
			const std::string message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			LogMessage(s_CoreLogger, level, message);
		}

		template<typename... Args>
		static void ClientLog(LogLevel level, std::string_view fmt, Args&&... args)
		{
			const std::string message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			LogMessage(s_ClientLogger, level, message);
		}

	private:
		static const std::string s_CoreLogger;
		static const std::string s_ClientLogger;

		static void LogMessage(std::string loggerID, LogLevel level, const std::string& message);
	};

	
#define LOG_CORE(...)      Forgex::Debug::Log::CoreLog(__VA_ARGS__)
#define LOG_CLIENT(...)    Forgex::Debug::Log::ClientLog(__VA_ARGS__)
}