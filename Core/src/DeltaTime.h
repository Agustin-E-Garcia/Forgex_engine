#pragma once
#include "Exports.h"
#include "GLFW/glfw3.h"

class ENGINE_API DeltaTime 
{
public:
	static void Init()
	{
		if(s_Instance == nullptr) s_Instance = new DeltaTime();
	}

	static void Update() { s_Instance->UpdateImp(); };
	static float GetTime() { return s_Instance->GetTimeImp(); };

private:
	DeltaTime();
	~DeltaTime();
	static DeltaTime* s_Instance;

	float m_DeltaTime;
	double m_LastTime;

	void UpdateImp();
	float GetTimeImp();
};