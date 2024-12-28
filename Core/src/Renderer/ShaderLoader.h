#pragma once
#include "Exports.h"

class ENGINE_API ShaderLoader
{
public:
	static int LoadShader(const char* vertexShader, const char* fragmentShader);
};

