#pragma once
#include "Exports.h"
#include "GLFW/glfw3.h"

class ENGINE_API DeltaTime 
{
public:
	DeltaTime();
	~DeltaTime();

	void Update();
	inline float GetDeltaTime() { return m_DeltaTime; }

private:
	float m_DeltaTime;
	double m_LastFrame;

	int m_NbFrames;
	double m_LastTime;

	unsigned int m_FrameDrawKey;
	unsigned int m_FPSKey;
};