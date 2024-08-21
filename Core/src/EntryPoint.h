#pragma once

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	auto instance = CreateApplication();
	instance->Run();
	delete instance;
	return 0;
}