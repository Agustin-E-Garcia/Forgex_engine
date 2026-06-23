#pragma once

namespace Forgex::Engine::Input
{
    struct PlayerInput
    {
        float m_MovementSpeed = 50.0f;
        float m_RotationSpeed = 0.3f;
        float m_PitchLimit = 89.0f;
    };
}
