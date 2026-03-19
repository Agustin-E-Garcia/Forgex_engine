#pragma once
#include "../DebugExports.h"
#include <functional>
#include <string>
#include <unordered_map>

namespace Forgex::Debug
{
    struct ConsoleCommand
    {
        std::function<void()> m_Function;
        std::string m_Description;
    };

    class DEBUG_API Command
    {
    public:
        Command();
        ~Command();

        static Command& Get();

        void Register(std::string command, std::function<void()> function, std::string description);
        void Execute(std::string command);

        static void PrintDescription(std::string command);

    private:
        std::unordered_map<std::string, ConsoleCommand> m_Commands;

        Command(const Command&) = delete;
        Command(Command&&) = delete;
        Command& operator=(const Command&) = delete;
        Command& operator=(Command&&) = delete;
    };

#define REGISTER_COMMAND(...) Forgex::Debug::Command::Get().Register(__VA_ARGS__)
}
