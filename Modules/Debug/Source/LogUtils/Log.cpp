#include "Log.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <mutex>
#include <queue>

namespace Forgex::Debug
{
    static LogLevel SpdlogLevelToLogLevel(spdlog::level::level_enum level)
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

    class ConsoleSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        std::queue<ConsoleMessage> m_MessageQueue;

        bool HasMessages() { return !m_MessageQueue.empty(); }

        ConsoleMessage GetNextMessage()
        {
            ConsoleMessage info = m_MessageQueue.front();
            m_MessageQueue.pop();
            return { info.text, info.level };
        }

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            spdlog::memory_buf_t formatted;
            spdlog::sinks::base_sink<std::mutex>::formatter_->format(msg, formatted);

            m_MessageQueue.emplace(fmt::to_string(formatted), SpdlogLevelToLogLevel(msg.level));
        }
        void flush_() override {}
    };

	const std::string Log::s_CoreLogger = "CORE";
	const std::string Log::s_ClientLogger = "APPLICATION";
	
    static std::shared_ptr<ConsoleSink> s_ConsoleSink = nullptr;

	void Log::Init()
	{
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_ConsoleSink = std::make_shared<ConsoleSink>();
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Forgex.log", true);
        auto terminalSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

        spdlog::sinks_init_list sinks = { s_ConsoleSink, fileSink, terminalSink };

        auto coreLogger = std::make_shared<spdlog::logger>(s_CoreLogger, sinks);
        coreLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(coreLogger);

        auto clientLogger = std::make_shared<spdlog::logger>(s_ClientLogger, sinks);
        clientLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(clientLogger);

        LOG_CORE(LogLevel::Info, "Logger {0} initialized", s_CoreLogger);
        LOG_CORE(LogLevel::Info, "Logger {0} initialized", s_ClientLogger);
    }

    bool Log::HasConsoleMessage() { return s_ConsoleSink->HasMessages(); }
    ConsoleMessage Log::GetNextConsoleMessage() { return s_ConsoleSink->GetNextMessage(); }

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
