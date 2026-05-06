#pragma once
#ifdef _WIN32
	#ifdef VOXEL_DLL
		#define VOXEL_API __declspec(dllexport)
	#else
		#define VOXEL_API __declspec(dllimport)
	#endif
#else
	#define VOXEL_API
#endif