#pragma once
#include "Exports.h"
#include <map>
#include <vector>
#include <string>

struct ProfileInfo 
{
	std::string m_Label;
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