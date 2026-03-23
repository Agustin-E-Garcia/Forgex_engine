#pragma once
#include "../Layer/Event/EventList.h"
#include <string>
#include <functional>

namespace Forgex::Core::Interfaces
{
    using EventCallbackFn = std::function<void(Layer::Event::Event&)>;

    class ILayer
    {
    public:

        ILayer(std::string name) : m_Name(name) {}
        virtual ~ILayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnBegin() = 0;
        virtual void OnEnd() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnEvent(Layer::Event::Event* event) = 0;
        virtual void OnRender() = 0;

        std::string GetName() const { return m_Name; }
        void SetCallbackFn(const EventCallbackFn& callback) { m_CallbackFn = callback; }

    protected:
        EventCallbackFn m_CallbackFn;

    private:
        std::string m_Name;
    };
}
