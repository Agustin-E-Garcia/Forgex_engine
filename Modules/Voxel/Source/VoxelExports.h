#pragma once
#if WIN32
	#if VOXEL_DLL
		#define VOXEL_API __declspec(dllexport)
	#else
		#define VOXEL_API __declspec(dllimport)
	#endif
#else
	#define VOXEL_API
#endif
