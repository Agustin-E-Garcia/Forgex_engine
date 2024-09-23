#include "DeltaTime.h"
#include "Profiler.h"

DeltaTime* DeltaTime::s_Instance = nullptr;

DeltaTime::DeltaTime() : m_DeltaTime(0.0f), m_LastFrame(glfwGetTime()), m_NbFrames(0), m_LastTime(glfwGetTime()) 
{
	m_FPSKey = Profiler::AddProfile("FPS", m_NbFrames);
	m_FrameDrawKey = Profiler::AddProfile("Frame draw time", m_NbFrames);
}

DeltaTime::~DeltaTime() {}

float DeltaTime::UpdateImp()
{
	float currentTime = glfwGetTime();
	m_DeltaTime = currentTime - m_LastFrame;
	m_LastFrame = currentTime;

	m_NbFrames++;
	if (currentTime - m_LastTime > 1.0f) 
	{
		Profiler::UpdateProfile(m_FrameDrawKey, 1000.0 / double(m_NbFrames));
		Profiler::UpdateProfile(m_FPSKey, m_NbFrames);
		m_NbFrames = 0;
		m_LastTime += 1.0f;
	}

	return m_DeltaTime;
}