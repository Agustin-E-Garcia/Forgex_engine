#pragma once
#include <string>

namespace Forgex::Graphics::Resources
{
const std::string CommonHeader = R"(
#version 420 core

struct DirectionalLight
{
    vec4 direction;
    vec4 color;
};

struct PointLight
{
    vec3 position;
    float constant;
    vec3 color;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec4 position;
    vec3 direction;
    float cutOff;
    vec4 color;
};

layout(std140, binding = 0) uniform FrameBlock
{
    mat4 view;
    mat4 projection;
    vec4 cameraPosition;
    float time;

    int directionalLightCount;
    int pointLightCount;
    int spotLightCount;

    DirectionalLight directionalLights[5];
    PointLight pointLights[5];
    SpotLight spotLights[5];
};
)";

const std::string VertexHeader = R"(
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
uniform mat4 model;
)";

const std::string FragmentHeader = R"(
struct Material
{
    vec3 diffuse;
    sampler2D diffuseMap;
    vec3 specular;
    float shininess;
};

uniform Material material;
out vec4 FragColor;
)";
}
