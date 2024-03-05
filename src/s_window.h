#pragma once
#include "window.h"
#include "s_render.h"

// Header for window
class SWindow : public UWindow {
    public:
        SWindow() : bIsRunning_(true), window_(nullptr) {
            renderer_ = std::make_unique<SRenderer>();
        }

        void* GetNativeWindow() override { return window_;}
        void SetNativeWindow(void* window) override {window_ = static_cast<GLFWwindow*>(window);}

        void HandleKeyInput(int key, int scancode, int action, int mods) override;
        void HandleWindowResize(int w, int h) override;

        void init(int w, int h, const std::string& t);
        void render();

        bool isRunning() {return bIsRunning_;}

    private:
        GLFWwindow* window_;
        std::unique_ptr<SRenderer> renderer_;
        bool bIsRunning_;
};
