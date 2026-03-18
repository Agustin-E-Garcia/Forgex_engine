#pragma once
#include <imgui.h>

namespace Forgex::UI
{
	class GUIWindow
	{
	public:
		GUIWindow(const char* name, bool isActive = false) : m_Name(name), m_IsActive(isActive) {}
		~GUIWindow() {}

        void ToggleWindow() { m_IsActive = !m_IsActive; }

		void Draw()
		{
			if(!m_IsActive) return;

			ImGui::Begin(m_Name);
			OnDraw();
			ImGui::End();
		}

        void Update() { OnUpdate(); }
	protected:
		virtual void OnDraw() {};
		virtual void OnUpdate() {};
	private:
		bool m_IsActive = false;
		const char* m_Name;
	};
}
