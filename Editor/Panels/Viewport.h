#pragma once
#include "../UI/GUIWindow.h"
#include <functional>
#include <stdint.h>

namespace Forgex::UI::Panels
{
	class Viewport : public GUIWindow
	{
		using ViewportResizeCallbackFn = std::function<void(float width, float height)>;
	public:
		Viewport(unsigned int viewportFramebufferID, ViewportResizeCallbackFn callback) : GUIWindow("Viewport", true),
			m_ViewportFramebuffer(viewportFramebufferID), m_Callback(callback) {}
		~Viewport() {}
	protected:
		virtual void OnDraw() override 
		{
			ImVec2 size = ImGui::GetContentRegionAvail();
			m_Callback(size.x, size.y);
			ImGui::Image((ImTextureID)(intptr_t)m_ViewportFramebuffer, size, ImVec2(0, 1), ImVec2(1, 0));
		}
	private:
		unsigned int m_ViewportFramebuffer;
		ViewportResizeCallbackFn m_Callback;
	};
}
