#include "TextureLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include "Log.h"

bool CheckBMPData(unsigned char  BMPheader[], FILE* BMPfile)
{
	if (!BMPfile)
	{
		LOG_CORE_ERROR("Image could not be opened");
		return false;
	}

	if (fread(BMPheader, 1, 54, BMPfile) != 54)
	{
		LOG_CORE_ERROR("Not a correct BMP file");
		return false;
	}

	if (BMPheader[0] != 'B' || BMPheader[1] != 'M')
	{
		LOG_CORE_ERROR("Not a correct BMP file\n");
		return false;
	}
}

unsigned int TextureLoader::LoadTexture(const char* filePath)
{
	LOG_CORE_INFO("Loading texture: {0}", filePath);

	unsigned char header[54];
	BMPData bmph;
	FILE* file;
	fopen_s(&file, filePath, "rb");

	if (CheckBMPData(header, file))
	{
		bmph.dataPos = *(int*)&(header[0x0A]);
		bmph.imageSize = *(int*)&(header[0x22]);
		bmph.width = *(int*)&(header[0x12]);
		bmph.height = *(int*)&(header[0x16]);
	}

	if (bmph.imageSize == 0)
		bmph.imageSize = bmph.width * bmph.height * 3;
	if (bmph.dataPos == 0)
		bmph.dataPos = 54;

	bmph.data = new char[bmph.imageSize];
	fread(bmph.data, 1, bmph.imageSize, file);
	fclose(file);
	
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmph.width, bmph.height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmph.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}