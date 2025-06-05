#pragma once
#include "UIExport.h"

namespace Forgex::UI::Elements
{
	static bool UI_API Button(const char* label, float width, float height);
	static void UI_API Float(const char* label, float& value, float step = 0.05f);
	static void UI_API Separator(const char* label);
	static void UI_API Image(unsigned int textureID, float width, float height);
}
