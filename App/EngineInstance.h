#pragma once
#include <Engine.h>

class EngineInstance : public Application
{
public:
	EngineInstance();
	~EngineInstance();
};

Application* CreateApplication()
{
	return new EngineInstance();
}