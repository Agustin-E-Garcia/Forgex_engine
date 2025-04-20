#pragma once
#include <ForgexDebugTools.h>
#include <exception>

extern Application* CreateApplication();

inline int main(int argc, char** argv)
{
	try
	{
		auto instance = CreateApplication();
		instance->Run();
		delete instance;
		return 0;
	}
	catch (std::runtime_error& e)
	{
		LOG_CORE(Forgex::Debug::Critical, e.what());
	}
}