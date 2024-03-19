#pragma once
#include "window.h"
#include "context/s_context.h"

// SWindow sits in between the main App class and the context class that handles rendering our entire
// application, acting as an intermediary between the two, handling small but important variables 
// such as screen size and the time between frames (delta_time).
class SWindow : public UWindow {
    public:
        SWindow();
        ~SWindow() {
            #ifdef SANDBOX_DEBUG
                std::cout << "Swindow is being destroyed!" << std::endl;
            #endif
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
        std::unique_ptr<SContext> renderer_;
        bool bIsRunning_;
        float delta_time_{0};
        float last_frame{0};
};
