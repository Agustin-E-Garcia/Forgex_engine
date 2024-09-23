#pragma once
#include "../Exports.h"
#include <glm/gtc/noise.hpp>

class ENGINE_API NoiseGenerator
{
public:
	
	static std::vector<float> GenerateNoiseMap(int startX, int endX, int startZ, int endZ, float scale, int octaves, float persistance, float lacunarity) 
	{
		int width = endX - startX;
		int height = endZ - startZ;
		std::vector<float> noiseMap;
		
		if (scale <= 0) scale = 0.001;
		
		for (int z = startZ; z < endZ; z++)
		{
			for (int x = startX; x < endX; x++)
			{
				float amplitude = 1;
				float frequency = 1;
				float noiseHeight = 1;
		
				for (int i = 0; i < octaves; i++)
				{
					float sampleX = x / scale * frequency;
					float sampleZ = z / scale * frequency;
		
					float perlinValue = glm::perlin(glm::vec2(sampleX, sampleZ));
					noiseHeight += perlinValue * amplitude;
					perlinValue = (perlinValue + 1.0f) * 0.5f;
		
					amplitude *= persistance;
					frequency *= lacunarity;
				}
		
				noiseMap.push_back(std::pow(noiseHeight, 6));
			}
		}

		return noiseMap;
	}
};