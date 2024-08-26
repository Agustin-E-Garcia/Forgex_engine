#pragma once
#include "Exports.h"
#include "glm/glm.hpp"

class ENGINE_API InputDetector
{
public:
	static void Init();
	static bool IsKeyPressed(int key);
};

#define IS_KEY_PRESSED(...)    InputDetector::IsKeyPressed(__VA_ARGS__)

#define KEY_D			68
#define KEY_A			65
#define KEY_S			83
#define KEY_W			87
#define KEY_SPACE		32
#define KEY_LEFT_SHIFT	340