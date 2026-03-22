#pragma once

namespace Forgex::Engine::Input
{
    struct PlayerInput
    {
        float m_MovementSpeed = 10.0f;
        float m_RotationSpeed = 0.3f;
        float m_Yaw = 0.0f;
        float m_Pitch = 0.0f;
        float m_PitchLimit = 89.0f;
    };
}
