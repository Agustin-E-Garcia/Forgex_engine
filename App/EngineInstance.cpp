#include "EngineInstance.h"
#include "EngineUIOverlay.h"

EngineInstance::EngineInstance()
{
	PushOverlay(new EngineUIOverlay());
}

EngineInstance::~EngineInstance()
{
}