#pragma once
#include "Exports.h"

enum VoxelType
{
	Default = 0
};

class ENGINE_API Voxel 
{
public:
	Voxel() : m_Active(true), m_Type(VoxelType::Default) {}
	~Voxel() {}

	bool IsActive() { return m_Active; }
	void SetActive(bool active) { m_Active = active; }

	VoxelType GetType() { return m_Type; }
	void SetType(VoxelType newType) { m_Type = newType; }
private:
	bool m_Active;
	VoxelType m_Type;
};