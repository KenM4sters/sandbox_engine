#pragma once
#include "window.h"
#include "render/s_context.h"

// Header for window
class SWindow : public UWindow {
    public:
        SWindow(bool bPostProcess);
        ~SWindow() {}
        void* GetNativeWindow() override { return window_;}
        void SetNativeWindow(void* window) override {window_ = static_cast<GLFWwindow*>(window);}

        void HandleKeyInput(int key, int scancode, int action, int mods) override;
        void HandleWindowResize(int w, int h) override;

        void init(int w, int h, const std::string& t);
        void render();

        bool isRunning() {return bIsRunning_;}

    private:
        GLFWwindow* window_;
        Shader* post_processing_shader_; 
        std::unique_ptr<SContext> renderer_;
        std::shared_ptr<PostProcessing> post_processing_;
        bool bPostProcessingEnabled;
        bool bIsRunning_;
        float delta_time_{0};
        float last_frame{0};
};
