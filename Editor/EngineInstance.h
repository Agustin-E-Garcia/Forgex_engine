#pragma once
#include <ForgexCore.h>

class EngineInstance : public Application
{
public:
    EngineInstance();
    ~EngineInstance();
};

inline Application* CreateApplication()
{
    return new EngineInstance();
}