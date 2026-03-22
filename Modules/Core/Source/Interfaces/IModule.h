#pragma once

namespace Forgex::Core { class EngineCore; }

namespace Forgex::Core::Interfaces
{
    class IModule
    {
    public:
        virtual ~IModule() = default;

        virtual void Init(EngineCore& core) = 0;
        virtual void Update(float deltaTime) {}
        virtual void Shutdown() = 0;
        virtual const char* GetName() const = 0;
    };
}
