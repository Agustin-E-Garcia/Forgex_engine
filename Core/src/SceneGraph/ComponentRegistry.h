#pragma once
#include "../Exports.h"
#include "Object.h"
#include <unordered_map>
#include <functional>
#include <vector>

class ComponentRegistry 
{
public:
	using FactoryFunc = std::function<void(Object&)>;

	static ComponentRegistry& Instance() 
	{
		static ComponentRegistry instance;
		return instance;
	}

	void ExecuteFactory(const char* name, Object& obj) 
	{
		m_Factories[name](obj);
	}

	template<typename T>
	void RegisterComponent(const char* name)
	{
		m_Factories[name] = [](Object& obj) { obj.AddComponent<T>(); };
	}

	std::vector<const char*> GetRegistryNames() 
	{
		std::vector<const char*> names;
		names.reserve(m_Factories.size());

		for (auto it = m_Factories.begin(); it != m_Factories.end(); it++)
		{
			names.emplace_back(it->first);
		}

		return names;
	}

private:
	std::unordered_map<const char*, FactoryFunc> m_Factories;
};

#define REGISTER_COMPONENT(type) static const bool registered_##type = (ComponentRegistry::Instance().RegisterComponent<type>(#type), true);