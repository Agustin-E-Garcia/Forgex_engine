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

	static float Update() { return s_Instance->UpdateImp(); };

private:
	DeltaTime();
	~DeltaTime();
	static DeltaTime* s_Instance;

	float m_DeltaTime;
	double m_LastFrame;

	int m_NbFrames;
	double m_LastTime;

	unsigned int m_FrameDrawKey;
	unsigned int m_FPSKey;

	float UpdateImp();
};