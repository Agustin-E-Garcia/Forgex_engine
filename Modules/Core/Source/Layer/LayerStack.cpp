#include "LayerStack.h"
#include "Event/Event.h"
#include <algorithm>

namespace Forgex::Core::Layer
{
    LayerStack::LayerStack()
    {
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (Interfaces::ILayer* layer : m_Layers)
        delete layer;
    }

    void LayerStack::PushLayer(Interfaces::ILayer* layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
        layer->SetCallbackFn(BIND_EVENT_FUNCTION(LayerStack::OnEvent));
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Interfaces::ILayer* overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->SetCallbackFn(BIND_EVENT_FUNCTION(LayerStack::OnEvent));
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Interfaces::ILayer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerInsert--;

            layer->OnDetach();
        }
    }

    void LayerStack::PopOverlay(Interfaces::ILayer* overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
            overlay->OnDetach();
        }
    }

    void LayerStack::OnEvent(Event::Event& event) { m_Callback(event); }
}
