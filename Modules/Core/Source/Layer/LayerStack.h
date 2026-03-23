#pragma once
#include "../Interfaces/ILayer.h"

namespace Forgex::Core::Layer
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Interfaces::ILayer* layer);
		void PushOverlay(Interfaces::ILayer* overlay);
		void PopLayer(Interfaces::ILayer* layer);
		void PopOverlay(Interfaces::ILayer* overlay);

        template<class T>
		T* GetLayerOfType() const
		{
			static_assert(std::is_base_of<Interfaces::ILayer, T>::value, "T must inherit from ILayer");

			for (Interfaces::ILayer* layer : m_Layers)
			{
				if (T* castedLayer = dynamic_cast<T*>(layer)) return castedLayer;
			}

			return nullptr;
		}

        void SetEventCallback(const Interfaces::EventCallbackFn& callback) { m_Callback = callback; }

		std::vector<Interfaces::ILayer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Interfaces::ILayer*>::iterator end() { return m_Layers.end(); }

	private:
        void OnEvent(Event::Event& event);

        std::vector<Interfaces::ILayer*> m_Layers;
		std::vector<Interfaces::ILayer*>::iterator m_LayerInsert;
        Interfaces::EventCallbackFn m_Callback;
	};
}
