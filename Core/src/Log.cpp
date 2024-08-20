#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

const std::string Log::s_CoreLogger = "CORE";
const std::string Log::s_ClientLogger = "APPLICATION";

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	spdlog::stderr_color_mt(s_CoreLogger)->set_level(spdlog::level::trace);
	spdlog::stderr_color_mt(s_ClientLogger)->set_level(spdlog::level::trace);
}