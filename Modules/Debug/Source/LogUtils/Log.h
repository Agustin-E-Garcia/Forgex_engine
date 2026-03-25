#pragma once
#include <memory>
#include <string>
#include <format>

namespace Forgex::Debug
{
    class ConsoleSink;

    enum LogLevel
    {
        Trace,
        Info,
        Warning,
        Error,
        Critical
    };

    class LogManager
    {
    public:
        LogManager();
        ~LogManager();

        template<typename... Args>
        void CoreLog(LogLevel level, std::string_view fmt, Args&&... args)
        {
            const std::string message = std::vformat(fmt, std::make_format_args(args...));
            LogMessage(m_CoreLogger, level, message);
        }

        template<typename... Args>
        void ClientLog(LogLevel level, std::string_view fmt, Args&&... args)
        {
            const std::string message = std::vformat(fmt, std::make_format_args(args...));
            LogMessage(m_ClientLogger, level, message);
        }

        bool GetNextConsoleMessage(std::string& message, LogLevel& level);

    private:
        const std::string m_CoreLogger = "CORE";
        const std::string m_ClientLogger = "APPLICATION";

        std::shared_ptr<ConsoleSink> m_ConsoleSink = nullptr;

        void LogMessage(std::string loggerID, LogLevel level, const std::string& message);
    };
}
