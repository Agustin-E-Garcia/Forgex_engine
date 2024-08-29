#pragma once
#include "Exports.h"

class ENGINE_API InputManager
{
public:
	static void Init() { if (s_Instance == nullptr) s_Instance = new InputManager(); }
	static void Update() { s_Instance->UpdateImp(); };
	static bool IsKeyPressed(int key);
	static void GetMouseInput(float* x, float* y);

private:
	InputManager();
	~InputManager();
	static InputManager* s_Instance;

	float lastXPosition;
	float lastYPosition;
	float offsetX;
	float offsetY;

	void UpdateImp();
};

#define IS_KEY_PRESSED(...)    InputManager::IsKeyPressed(__VA_ARGS__)

#define KEY_D			68
#define KEY_A			65
#define KEY_S			83
#define KEY_W			87
#define KEY_SPACE		32
#define KEY_LEFT_SHIFT	340