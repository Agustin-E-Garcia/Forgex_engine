#include "UIWindowManager.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <backends/imgui_impl_opengl3.h>

namespace Forgex::Editor::UI
{
    UIWindowManager::UIWindowManager()
    {
    	IMGUI_CHECKVERSION();
    	m_ActiveContext = ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO();
    	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    	io.DisplaySize = ImVec2(800, 600);
    	io.KeyRepeatRate = 0.5f;

    	ImGui::StyleColorsDark();
    	ImGui_ImplOpenGL3_Init();
    }

    UIWindowManager::~UIWindowManager()
    {
        for(GUIWindow* window : m_WindowCollection)
            delete window;

        m_WindowCollection.clear();

    	ImGui_ImplOpenGL3_Shutdown();
    	ImGui::DestroyContext();
    }

    void UIWindowManager::SetContext()
    {
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(m_ActiveContext));
    }

    void UIWindowManager::Update(float deltaTime)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(0U, 0, ImGuiDockNodeFlags_PassthruCentralNode);

        for(GUIWindow* window : m_WindowCollection)
            window->Update();
   }

    void UIWindowManager::Render()
    {
    	if (!m_WindowActive) return;

        for(GUIWindow* window : m_WindowCollection)
            window->Draw();

    	ImGui::Render();
    	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
