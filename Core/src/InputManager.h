#pragma once
#include "Exports.h"

class ENGINE_API InputManager
{
public:
	static bool IsKeyPressed(int keyCode);
	static float IsMouseButtonPressed(int button);
	static void GetMousePosition(float& xPositon, float& yPosition);

private:
	InputManager() = default;
	~InputManager() = default;
};