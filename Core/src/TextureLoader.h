#pragma once
#include "Exports.h"

struct BMPData
{

};

class ENGINE_API TextureLoader
{
public:
	static unsigned int LoadTexture(const char* filePath);
private:
	static unsigned int GenerateTexture(unsigned int internalFormat, int width, int height, unsigned int format, unsigned int type, const void* data);
};

