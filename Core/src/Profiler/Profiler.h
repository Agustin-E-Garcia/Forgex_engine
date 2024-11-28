#pragma once
#include "../pch.h"
#include "../Exports.h"
#include <chrono>

struct ENGINE_API ProfileInfo 
{
	const char* m_Label = nullptr;
	double m_Value = -1;

	void Update(double value) {	m_Value = value; }

	ProfileInfo(const char* name, double value)
	{
		m_Label = name;
		m_Value = value;
	}
};

class ENGINE_API Profiler
{
public:
	static int32_t AddProfile(const char* name, double value)
	{
		Profiler& instance = GetInstance();
		int32_t key = instance.m_TimerMap.size() + 1;
		instance.m_TimerMap.emplace(key, ProfileInfo(name, value));
		return key;
	}

	static void UpdateProfile(int32_t key, double value)
	{
		auto it = GetInstance().m_TimerMap.find(key);
		if (it != End())
		{
			it->second.Update(value);
		}
	}

	static const ProfileInfo* GetProfile(int32_t key)
	{
		auto it = GetInstance().m_TimerMap.find(key);
		if (it != End()) return &it->second;
		return nullptr;
	}

	/// <summary>
	/// Iterates over all the Profiles calling function over each of them
	/// </summary>
	/// <param name="function"> The function that will be called over each profile </param>
	static void ExecuteOverProfiles(std::function<void(const ProfileInfo&)> function)
	{
		for (auto it = Begin(); it != End(); it++)
		{
			function(it->second);
		}
	}

	static std::map<int32_t, ProfileInfo>::iterator Begin() { return GetInstance().m_TimerMap.begin(); }
	static std::map<int32_t, ProfileInfo>::iterator End() { return GetInstance().m_TimerMap.end(); }

private:
	std::map<int32_t, ProfileInfo> m_TimerMap;

	static Profiler& GetInstance()
	{
		static Profiler instance;
		return instance;
	}
};

class ENGINE_API FunctionTimer
{
public:
	FunctionTimer(const char* name, int* profilerKey)
	{
		if (*profilerKey < 0) *profilerKey = Profiler::AddProfile(name, 0);

		m_profilerKey = *profilerKey;
		m_startPoint = std::chrono::high_resolution_clock::now(); 
	}

	~FunctionTimer()
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