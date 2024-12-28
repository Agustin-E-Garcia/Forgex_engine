#pragma once
#include <Engine.h>

class Viewport : public Menu
{
public:
	Viewport() : Menu("Viewport") {}
	~Viewport() {}

	RenderTarget& GetRenderTarget() { return m_RenderTarget; }

protected:
	void OnDraw() override
	{
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		m_RenderTarget.m_TargetWidth = viewportSize.x;
		m_RenderTarget.m_TargetHeight = viewportSize.y;

		ImGui::Image((void*)(intptr_t)m_RenderTarget.m_RenderTextureID, viewportSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
	}

private:
	RenderTarget m_RenderTarget;
};