#pragma once
#include "UIExport.h"

namespace Forgex::UI::Elements
{
	bool UI_API Button(const char* label, float width, float height);
	void UI_API Float(const char* label, float& value, float step = 0.05f);
	void UI_API Separator(const char* label);
	void UI_API Image(unsigned int textureID, float width, float height);
	void UI_API GetAvailableContentSize(float& width, float& height);
}
