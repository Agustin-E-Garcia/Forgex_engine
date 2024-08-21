#pragma once
#include "Exports.h"

struct BMPData
{
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	char* data;
};

class ENGINE_API TextureLoader
{
public:
	static unsigned int LoadTexture(const char* filePath);
};

