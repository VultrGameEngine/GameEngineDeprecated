#include "../../include/editor/editor.hpp"
#include "../../include/core/systems/render_system.h"
#include "../../include/editor/core/windows/scene_window.hpp"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Editor::Editor::Editor()
{
    windows.push_back(new SceneWindow());
}

Editor::Editor::~Editor()
{
    windows.clear();
    windows.shrink_to_fit();
}

void Editor::Editor::Render()
{
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, RenderSystem::Get()->render_texture);

    ImGui_ImplOpenGL3_NewFrame();

    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    static bool dockspaceOpen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar(3);
    ImGui::TextUnformatted("Talskdjflkasj");
    Get()->dockspace = ImGui::GetID("HUB_DockSpace");
    ImGui::DockSpace(Get()->dockspace, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoResize);

    for (Window *window : Get()->windows)
    {
        ImGui::SetNextWindowDockID(Get()->dockspace, ImGuiCond_FirstUseEver);
        window->Render();
    }
    ImGui::End();
    // ImGui::PopStyleVar();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
    glEnable(GL_DEPTH_TEST);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}