#pragma once
#include <Engine.h>

class ProfileViewer : public Menu
{
public:
	ProfileViewer() : Menu("Profiler") {}
	~ProfileViewer() {}

protected:
	void OnDraw() override
	{
		Profiler::ExecuteOverProfiles(BIND_EVENT_FUNCTION(ProfileViewer::DrawProfile));
	}

	void DrawProfile(const ProfileInfo& info)
	{
		ImGui::Separator();
		char text[50];
		sprintf(text, "%s: %.3fms", info.m_Label, info.m_Value);
		ImGui::Text(text);
	}
};