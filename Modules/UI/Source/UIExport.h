#pragma once
#if UI_DLL
#define UI_DLL __declspec(dllexport)
#else
#define UI_DLL __declspec(dllimport)
#endif