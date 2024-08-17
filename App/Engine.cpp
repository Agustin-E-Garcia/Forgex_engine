#include "Engine.h"

bool Engine::OnStart()
{
    std::cout << "Engine::Start()" << std::endl;
    return true;
}

bool Engine::OnQuit()
{
    std::cout << "Engine::Quit()" << std::endl;
    return true;
}

bool Engine::OnLoop()
{
    std::cout << "Engine::Loop()" << std::endl;
    return true;
}