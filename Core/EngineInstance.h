#pragma once
#include "Exports.h"

class ENGINE_API EngineInstance 
{
private:
	bool m_Quit = false;

protected:
	virtual bool OnStart() = 0;
	virtual bool OnQuit() = 0;
	virtual bool OnLoop() = 0;

public:
	bool Start();
	bool Quit();
	void Loop();
};