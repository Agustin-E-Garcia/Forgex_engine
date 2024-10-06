#pragma once
#include "Layer.h"

class ENGINE_API LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* overlay);

	template<class T>
	T* GetLayerOfType() const
	{
		static_assert(std::is_base_of<Layer, T>::value, "T must inherit from Layer");

		for (Layer* layer : m_Layers)
		{
			if (T* castedLayer = dynamic_cast<T*>(layer)) return castedLayer;
		}

		return nullptr;
	}

	std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
	std::vector<Layer*>::iterator end() { return m_Layers.end(); }

private:
	std::vector<Layer*> m_Layers;
	std::vector<Layer*>::iterator m_LayerInsert;
};