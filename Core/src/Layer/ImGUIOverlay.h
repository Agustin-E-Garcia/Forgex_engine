#pragma once
#include "Layer.h"
#include "../Application.h"

#include <imgui/imgui.h>
#include <imgui/backends/OpenGL/imgui_impl_opengl3.h>

class ENGINE_API ImGUIOverlay : public Layer
{
public:
	ImGUIOverlay() : Layer("ImGUI") {}
	
	~ImGUIOverlay() 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void OnAttach() override
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		ImGui_ImplOpenGL3_Init();
	}

	void OnUpdate(float deltaTime) override 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1720.0f, 1080.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
	}

	void OnRender() override
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void OnEvent(Event& event) override
	{
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<MousePositionEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMousePosition));
		dispatcher.Dispatch<MouseClickEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMouseClick));
		dispatcher.Dispatch<MouseUnclickEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMouseUnclicked));
	}

	bool OnMousePosition(MousePositionEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetPositionX(), e.GetPositionY());
		return false;
	}

	bool OnMouseClick(MouseClickEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = true;
		return false;
	}

	bool OnMouseUnclicked(MouseUnclickEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = false;
		return false;
	}
};