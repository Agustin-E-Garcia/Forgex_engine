#include "DrawElements.h"
#include <cstdint>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace Forgex::UI::Elements
{
	bool Button(const char* label, float width, float height) { return ImGui::Button(label, ImVec2(width, height)); }
	void Float(const char* label, float& value, float step) { ImGui::InputFloat(label, &value, step); }
	void Separator(const char* label) { ImGui::SeparatorText(label); }
	void Image(unsigned int textureID, float width, float height) { ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(width, height), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); }
	void GetAvailableContentSize(float& width, float& height) { ImVec2 size = ImGui::GetContentRegionAvail(); width = size.x; height = size.y; }
}
