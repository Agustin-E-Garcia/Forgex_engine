#pragma once
#include <functional>
#include "../Layer/Event/Event.h"

namespace Forgex::Core::Interfaces
{
    class IWindow
    {
    public:
        using EventCallbackFn = std::function<void(Layer::Event::Event&)>;

        virtual ~IWindow() = default;

        virtual void Update() = 0;
        virtual bool ShouldClose() const = 0;
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        virtual int GetWidth() { return m_Width; }
        virtual int GetHeight() { return m_Height; }

    protected:
        int m_Width;
        int m_Height;
    };
}
