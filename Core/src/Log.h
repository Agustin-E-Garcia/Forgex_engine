#pragma once

#include "Exports.h"
#include <spdlog/spdlog.h>

class ENGINE_API Log
{
public:
	static void Init();

	inline static auto GetCoreLogger() { return spdlog::get(s_CoreLogger); };
	inline static auto GetClientLogger() { return spdlog::get(s_ClientLogger); };

private:
	static const std::string s_CoreLogger;
	static const std::string s_ClientLogger;
};

#define LOG_CORE_TRACE(...)      Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)       Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)       Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)      Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...)   Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...)           Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)            Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)            Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)           Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)        Log::GetClientLogger()->critical(__VA_ARGS__)