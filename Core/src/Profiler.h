#pragma once
#include "Exports.h"
#include <map>
#include <vector>
#include <string>
#include <chrono>

struct ProfileInfo 
{
	const char* m_Label;
	double value;

	template<typename T>
	T ReadValue() {	return (T)value; }
};

class ENGINE_API Profiler
{
public:
	static int AddProfile(const char* label, double value);
	static ProfileInfo GetProfile(int profileKey);
	static void RemoveProfile(int profileKey);
	static void UpdateProfile(int profileKey, double value);

	static inline std::map<int, ProfileInfo>::iterator begin() { return s_Instance->m_Profiles.begin(); }
	static inline std::map<int, ProfileInfo>::iterator end() { return s_Instance->m_Profiles.end(); }

private:
	static Profiler* s_Instance;

	std::map<int, ProfileInfo> m_Profiles;
};

class ENGINE_API Timer 
{
public:
	Timer(const char* name, int* profilerKey)
	{
		if (*profilerKey < 0) *profilerKey = Profiler::AddProfile(name, 0);

		m_profilerKey = *profilerKey;
		m_startPoint = std::chrono::high_resolution_clock::now(); 
	}

	~Timer() 
	{
		auto endPoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

		float duration = (end - start) * 0.001f;

		Profiler::UpdateProfile(m_profilerKey, duration);
	}

private:
	std::chrono::steady_clock::time_point m_startPoint;
	int m_profilerKey;
};