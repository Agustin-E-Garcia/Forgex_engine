#pragma once
#include "../DebugExports.h"
#include <functional>
#include <string>
#include <unordered_map>

namespace Forgex::Debug
{
    struct Command
    {
        std::function<void()> m_Function;
        std::string m_Description;
    };

    class DEBUG_API CommandHandler
    {
    public:
        CommandHandler();
        ~CommandHandler();

        bool Register(std::string command, std::function<void()> function, std::string description);
        bool Execute(std::string command);

    private:
        std::unordered_map<std::string, Command> m_Commands;
    };

}
