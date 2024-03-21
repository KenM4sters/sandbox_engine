#pragma once
#include "../utils/includes.h"
#include "../../deps/ImGui/imgui.h"
#include "../../deps/ImGui/imgui_impl_glfw.h"
#include "../../deps/ImGui/imgui_impl_opengl3.h"


class UserInterface {
    public:
        UserInterface(GLFWwindow* window) : window_(window) {}
        void Init();
        void PreRender();
        void PostRender();
        void Terminate();
    private:
        GLFWwindow* window_;
        bool bShowDemoWindow_ = true;
        bool bShowAnotherWindow_ = false;
        ImGuiIO io_;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};