#pragma once
#include "Exports.h"
#include <stdint.h>

enum VoxelType : uint8_t // range 0 - 255
{
	Empty = 0,
	Default,
	Dirt,
	Water,
	Stone,
	TYPE_COUNT
};

class ENGINE_API Voxel 
{
public:
	Voxel() : m_Type(VoxelType::Default) {}
	Voxel(VoxelType type) : m_Type(type) {};
	~Voxel() {}

	bool IsActive() { return m_Type != VoxelType::Empty; }
	void SetActive(bool active) { m_Type = active ? VoxelType::Default : VoxelType::Empty; }

	VoxelType GetType() { return m_Type; }
	void SetType(VoxelType newType) { m_Type = newType; }
private:
	VoxelType m_Type;
};