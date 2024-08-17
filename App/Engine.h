#pragma once
#include <iostream>
#include <EngineInstance.h>

class Engine : public EngineInstance
{
protected:
	bool OnStart() override;
	bool OnQuit() override;
	bool OnLoop() override;
};