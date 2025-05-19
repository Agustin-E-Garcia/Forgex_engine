#pragma once
#include <ForgexCore.h>

class EngineInstance : public Forgex::Core::Application
{
public:
    EngineInstance();
    ~EngineInstance();
};

inline Forgex::Core::Application* CreateApplication()
{
    return new EngineInstance();
}