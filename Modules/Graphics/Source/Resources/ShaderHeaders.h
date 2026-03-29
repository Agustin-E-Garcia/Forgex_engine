#pragma once
#include <string>

namespace Forgex::Graphics::Resources
{
const std::string CommonHeader = R"(
#version 420 core

struct Light
{
    vec3 pos;
    float intensity;
    vec3 color;
    float radius;
};

layout(std140, binding = 0) uniform FrameBlock
{
    mat4 view;
    mat4 projection;
    vec3 cameraPosition;
    float time;
    Light lightData[16];
    int pointLightCount;
};
)";

const std::string VertexHeader = R"(
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
uniform mat4 model;
)";

const std::string FragmentHeader = R"(
uniform vec3 albedo;
out vec4 FragColor;
)";
}
