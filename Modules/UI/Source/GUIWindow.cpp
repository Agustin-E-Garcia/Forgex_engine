#include "GUIWindow.h"
#include <imgui.h>
#include <ForgexDebugTools.h>

namespace Forgex::UI 
{
	GUIWindow::GUIWindow(const char* name, bool isActive) : m_IsActive(isActive), m_Name(name) {}
	GUIWindow::~GUIWindow() {}

	void GUIWindow::Draw()
	{
		if(!m_IsActive) return;

		ImGui::Begin(m_Name);
		OnDraw();
		ImGui::End();
	}
}
