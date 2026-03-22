#include "Log.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "ConsoleSink.h"

namespace Forgex::Debug
{
    LogLevel SpdlogLevelToLogLevel(spdlog::level::level_enum level)
    {
        switch(level)
        {
            case spdlog::level::trace:    return Trace;
            case spdlog::level::info:     return Info;
            case spdlog::level::warn:     return Warning;
            case spdlog::level::err:      return Error;
            case spdlog::level::critical: return Critical;
            default:                      return Info;
        }
    }

    LogManager::LogManager()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_ConsoleSink = std::make_shared<ConsoleSink>();
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Forgex.log", true);
        auto terminalSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

        spdlog::sinks_init_list sinks = { m_ConsoleSink, fileSink, terminalSink };

        auto coreLogger = std::make_shared<spdlog::logger>(m_CoreLogger, sinks);
        coreLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(coreLogger);

        auto clientLogger = std::make_shared<spdlog::logger>(m_ClientLogger, sinks);
        clientLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(clientLogger);

        CoreLog(LogLevel::Info, "Logger {0} initialized", m_CoreLogger);
        CoreLog(LogLevel::Info, "Logger {0} initialized", m_ClientLogger);
    }

    LogManager::~LogManager() {}

    bool LogManager::GetNextConsoleMessage(std::string* message, LogLevel* level)
    {
        if(!m_ConsoleSink->HasMessages()) return false;

        ConsoleMessage msg = m_ConsoleSink->GetNextMessage();
        *message = msg.text;
        *level = SpdlogLevelToLogLevel(msg.level);
        return true;
    }

    void LogManager::LogMessage(std::string loggerID, LogLevel level, const std::string& message)
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
