#pragma once
#include "MathExports.h"

namespace Forgex::Math
{
    // ---- Foward Declarations ----//
    struct Vec3;
    struct Mat4;
    struct Quat;
    // -----------------------------//
    
    float MATH_API Pi();
    float MATH_API Clamp(float x, float minValue, float maxValue);
    float MATH_API Radians(float degrees);

    Vec3 MATH_API Normalize(Vec3 vector);
    
    Mat4 MATH_API Translate(Mat4 matrix, Vec3 vector);
    Mat4 MATH_API Scale(Mat4 matrix, Vec3 scalar);
    Mat4 MATH_API Mat4_Cast(Quat quaternion);
    Mat4 MATH_API Perspective(float fovy, float aspect, float near, float far);
    Mat4 MATH_API LookAt(Vec3 eye, Vec3 center, Vec3 up);
    Mat4 MATH_API GetRotationOnly(Mat4 matrix);
    
    Quat MATH_API AngleAxis(float angle, Vec3 axis);
}
