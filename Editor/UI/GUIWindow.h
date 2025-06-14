#pragma once
#include <imgui.h>

namespace Forgex::UI
{
	class GUIWindow
	{
	public:
		GUIWindow(const char* name, bool isActive = false) : m_Name(name), m_IsActive(isActive) {}
		~GUIWindow() {}

		void Draw()
		{
			if(!m_IsActive) return;

			ImGui::Begin(m_Name);
			OnDraw();
			ImGui::End();
		}
	protected:
		virtual void OnDraw() {};
		virtual void Update() {};
	private:
		bool m_IsActive = false;
		const char* m_Name;
	};
}
