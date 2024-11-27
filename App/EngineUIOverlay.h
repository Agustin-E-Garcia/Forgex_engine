#pragma once
#include "Menus/SceneInspector.h"
#include "Menus/ProfilerViewer.h"

class EngineUIOverlay : public ImGUIOverlay
{
public:
	EngineUIOverlay() : ImGUIOverlay() {};
	~EngineUIOverlay() 
	{
		delete m_SceneInspector;
		delete m_ProfileViewer;
	};

	void OnAttach() override
	{
		ImGUIOverlay::OnAttach();
		ImGui::SetCurrentContext(m_ImGuiContext);
		
		m_SceneInspector = new SceneInspector();
		m_ProfileViewer = new ProfileViewer();
	}

	void OnBegin() override
	{
		AddMenu(m_SceneInspector);
		AddMenu(m_ProfileViewer);
	}

	void OnUpdate(float deltaTime) override 
	{
		ImGUIOverlay::OnUpdate(deltaTime);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		for (Menu* menu : m_MenuCollection)
			menu->Draw();
	}

	void OnEvent(Event& e) override
	{
		ImGUIOverlay::OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<SceneChangeEvent>(BIND_EVENT_FUNCTION(EngineUIOverlay::OnSceneChangedEvent));
	}

	bool OnSceneChangedEvent(SceneChangeEvent& e)
	{
		m_SceneInspector->SetActiveScene(e.GetScene());
		return true;
	}

private:
	std::vector<Menu*> m_MenuCollection;

	SceneInspector* m_SceneInspector = nullptr;
	ProfileViewer* m_ProfileViewer = nullptr;

	void AddMenu(Menu* menu)
	{
		m_MenuCollection.emplace_back(menu);
	}

	void RemoveMenu(Menu* menu)
	{
		auto it = std::find(m_MenuCollection.begin(), m_MenuCollection.end(), menu);
		if (it != m_MenuCollection.end())
			m_MenuCollection.erase(it);
	}
};