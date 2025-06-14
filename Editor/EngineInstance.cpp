#include "EngineInstance.h"
#include "UILayer.h"

EngineInstance::EngineInstance() : Forgex::Core::Application()
{
	m_LayerStack.PushOverlay(new Forgex::UI::UILayer());
}

EngineInstance::~EngineInstance()
{
}
