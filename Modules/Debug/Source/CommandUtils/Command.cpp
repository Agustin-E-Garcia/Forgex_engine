#include "Command.h"
#include "../LogUtils/Log.h"
#include <format>

namespace Forgex::Debug
{
    Command& Command::Get()
    {
        static Command instance;
        return instance;
    }

    void Command::PrintDescription(std::string command)
    {
        if(!Command::Get().m_Commands.contains(command)) return;

        LOG_CORE(Debug::Info, "Command: {0} - {1}", command, Command::Get().m_Commands[command].m_Description);
    }

    Command::Command() {}
    Command::~Command() { m_Commands.clear(); }

    void Command::Register(std::string command, std::function<void()> function, std::string description)
    {
        if(m_Commands.contains(command)) return;
        m_Commands[command] = { function, description };

        std::string helpCommand = std::format("help_{0}", command);
        m_Commands[helpCommand] = { [command]() { PrintDescription(command); }, "" };
    }

    void Command::Execute(std::string command)
    {
        if(!m_Commands.contains(command))
        {
            LOG_CORE(Debug::Error, "Command '{0}' not found", command);
            return;
        }

        m_Commands[command].m_Function();
    }
}
