#pragma once
#include "Event/EventList.h"
#include <string>

namespace Forgex::Core::Layer
{
    class Layer
    {
    public:
        Layer(std::string name) : m_Name(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnBegin() = 0;
        virtual void OnEnd() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnEvent(Event::Event* event) = 0;
        virtual void OnRender() = 0;

        std::string GetName() const { return m_Name; }

    private:
        std::string m_Name;
    };
}
