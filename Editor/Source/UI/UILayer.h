#pragma once
#include <ForgexCore.h>

namespace Forgex::Editor::UI
{
    class UIOverlay : public Core::Layer::Layer
    {
    public:
        UIOverlay() : Core::Layer::Layer("UI Overlay") {}

        void OnAttach() override {}
        void OnDetach() override {}
        void OnBegin() override{}
        void OnEnd() override {}
        void OnUpdate(float deltaTime) override {}
        void OnEvent(Core::Layer::Event::Event* event) override {}
        void OnRender() override {}
    };
}
