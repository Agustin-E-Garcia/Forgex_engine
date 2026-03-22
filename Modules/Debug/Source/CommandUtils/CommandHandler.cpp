#include "CommandHandler.h"

namespace Forgex::Debug
{
    CommandHandler::CommandHandler() {}
    CommandHandler::~CommandHandler() { m_Commands.clear(); }

    bool CommandHandler::Register(std::string command, std::function<void()> function, std::string description)
    {
        if(m_Commands.contains(command)) return false;

        m_Commands[command] = { function, description };
        return true;
    }

    bool CommandHandler::Execute(std::string command)
    {
        if(!m_Commands.contains(command)) return false;

        m_Commands[command].m_Function();
        return true;
    }
}
