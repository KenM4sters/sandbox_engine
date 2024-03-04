#pragma once
#include "window.h"

// Header for window

namespace sandbox_window {
    class SWindow : public UWindow {
        public:
            SWindow() : bIsRunning_(true), window_(nullptr) {}
            ~SWindow();

            void* GetNativeWindow() override { return window_;}
            void SetNativeWindow(void* window) override {window_ = static_cast<GLFWwindow*>(window);}

            void HandleKeyInput(int key, int scancode, int action, int mods) override;
            void HandleWindowResize(int w, int h) override;

            void init(int w, int h, std::string& t);
            void render();

            bool isRunning() {return bIsRunning_;}

        private:
            GLFWwindow* window_;
            bool bIsRunning_;
    };
}