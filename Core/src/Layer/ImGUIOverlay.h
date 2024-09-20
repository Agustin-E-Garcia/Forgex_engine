#pragma once
#include "Layer.h"
#include "../Application.h"
#include "../TextureLoader.h"
#include "../Utils/NoiseGenerator.h"

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

		noisemapTexture = TextureLoader::LoadHeightmapIntoTexture(NoiseGenerator::GenerateNoiseMap(posX, posX + 32, posZ + 0, posZ + 32, scale, octaves, persistance, lacunarity).data(), 32, 32);
	}

	void OnUpdate(float deltaTime) override
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1720.0f, 1080.0f);

		Renderer::ToggleWireframe(m_WireframeActive);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		//ImGui::ShowDemoWindow();
		DisplayMenu();
		DisplayStats();
		DisplayNoiseGenerationMenu();
	}

	void DisplayMenu()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Utils"))
			{
				ImGui::Checkbox("Wireframe", &m_WireframeActive);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void DisplayStats() 
	{
		ImGui::SetNextWindowBgAlpha(0.35f);
		if (ImGui::Begin("Profiler"))
		{
			ImGui::Text("Displaying all profiles");
			ImGui::Separator();

			for (auto it = Profiler::begin(); it != Profiler::end(); it++)
			{
				ImGui::Text("%s: %.4f", it->second.m_Label, it->second.ReadValue<float>());
			}
		}
		ImGui::End();
	}

	void DisplayNoiseGenerationMenu() 
	{
		if (ImGui::Begin("Noise Generator")) 
		{
			ImGui::Text("Noisemap values");
			ImGui::SliderInt("Pos X", &posX, 1, 100);
			ImGui::SliderInt("Pos Z", &posZ, 1, 100);
			ImGui::SliderFloat("Scale", &scale, 0.1, 30);
			ImGui::SliderInt("Octaves", &octaves, 1, 30);
			ImGui::SliderFloat("Persistance", &persistance, 0.1, 30);
			ImGui::SliderFloat("Lacunarity", &lacunarity, 0.1, 30);
			
			glDeleteTextures(1, &noisemapTexture);
			noisemapTexture = TextureLoader::LoadHeightmapIntoTexture(NoiseGenerator::GenerateNoiseMap(posX, posX + 32, posZ +0, posZ + 32, scale, octaves, persistance, lacunarity).data(), 32, 32);

			ImGui::Separator();
			ImGui::Text("Generated Noisemap texture");
			ImGui::Text("size = %d x %d", 32, 32);
			ImGui::Image((void*)(intptr_t)noisemapTexture, ImVec2(256, 256));
		}
		ImGui::End();
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

private:
	bool m_WireframeActive = false;

	int posX = 0;
	int posZ = 0;
	float scale = 20.0f;
	int octaves = 4;
	float persistance = 0.5f;
	float lacunarity = 2.0f;

	unsigned int noisemapTexture = 0;
};