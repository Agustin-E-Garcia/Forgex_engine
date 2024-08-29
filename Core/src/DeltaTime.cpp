#include "DeltaTime.h"

DeltaTime* DeltaTime::s_Instance = nullptr;

DeltaTime::DeltaTime() : m_DeltaTime(0.0f), m_LastTime(glfwGetTime()) {}
DeltaTime::~DeltaTime() {}

void DeltaTime::UpdateImp()
{
	float currentTime = glfwGetTime();
	m_DeltaTime = currentTime - m_LastTime;
	m_LastTime = currentTime;
}

float DeltaTime::GetTimeImp() { return m_DeltaTime; }