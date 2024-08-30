#include "DeltaTime.h"

DeltaTime* DeltaTime::s_Instance = nullptr;

DeltaTime::DeltaTime() : m_DeltaTime(0.0f), m_LastTime(glfwGetTime()) {}
DeltaTime::~DeltaTime() {}

float DeltaTime::UpdateImp()
{
	float currentTime = glfwGetTime();
	m_DeltaTime = currentTime - m_LastTime;
	m_LastTime = currentTime;

	return m_DeltaTime;
}