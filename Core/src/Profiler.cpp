#include "Profiler.h"

Profiler* Profiler::s_Instance = new Profiler();

int Profiler::AddProfile(const char* label, double value)
{
	ProfileInfo info{};
	info.m_Label = label;
	info.value = value;

	int ID = s_Instance->m_Profiles.size();
	auto[it, result] = s_Instance->m_Profiles.try_emplace(ID, info);

	if (result) return ID;
	else return -1;
}

ProfileInfo Profiler::GetProfile(int profileKey)
{
	auto it = s_Instance->m_Profiles.find(profileKey);
	if (it != s_Instance->end()) 
	{
		return it->second;
	}

	return ProfileInfo();
}

void Profiler::RemoveProfile(int profileKey)
{
	auto it = s_Instance->m_Profiles.find(profileKey);
	if (it != s_Instance->end()) 
	{
		s_Instance->m_Profiles.erase(it);
	}
}

void Profiler::UpdateProfile(int profileKey, double value)
{
	auto it = s_Instance->m_Profiles.find(profileKey);
	if (it != s_Instance->end()) 
	{
		s_Instance->m_Profiles[profileKey].value = value;
	}
}