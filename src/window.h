#pragma once
#include "utils/includes.h"
#include "camera/camera.h"

// Base class for window

class UWindow {
    public:
        virtual void* GetNativeWindow() = 0;
        virtual void SetNativeWindow(void* window) = 0;

        virtual void HandleKeyInput(int key, int scancode, int action, int mods) = 0;
        virtual void HandleWindowResize(int w, int h) = 0;

        int width_, height_;
        std::string title_;

        // Camera related variables
        Camera* camera_ = new Camera(glm::vec3(-500.0f, 0.0f, -500.0f));
        // Current values of the mouse position
        float mouse_pos_x_;
        float mouse_pos_y_;
        // Previous values of the mouse position
        float prev_mouse_pos_x_;
        float prev_mouse_pos_y_;
        // Returns true when the mouse first enters the window
        bool bMouseIn_{true};
};