#pragma once
#include <spdlog/sinks/base_sink.h>
#include <mutex>
#include <queue>

namespace Forgex::Debug
{
    struct ConsoleMessage
    {
        std::string text;
        spdlog::level::level_enum level;
    };

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

            m_MessageQueue.emplace(fmt::to_string(formatted), msg.level);
        }
        void flush_() override {}
    };


}
