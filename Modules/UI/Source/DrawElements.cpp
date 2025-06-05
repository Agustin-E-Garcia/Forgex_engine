#include "DrawElements.h"
#include <cstdint>
#include <imgui.h>

namespace Forgex::UI::Elements
{
	bool Button(const char* label, float width, float height) { return ImGui::Button(label, ImVec2(width, height)); }
	void Float(const char* label, float& value, float step) { ImGui::InputFloat(label, &value, step); }
	void Separator(const char* label) { ImGui::SeparatorText(label); }
	void Image(unsigned int textureID, float width, float height) { ImGui::Image((intptr_t)textureID, ImVec2(width, height)); }
}
