#pragma once
#include "Log.h"

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	Log::Init();

	auto instance = CreateApplication();
	instance->Run();
	delete instance;
	return 0;
}