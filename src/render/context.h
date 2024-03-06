#pragma once
#include "../window.h"
#include "../scene/scene.h"

// Base class for rendering 

class UContext {
    public:
        UContext() : window_(nullptr) {scene_ = nullptr;}

        virtual void init(UWindow *window) = 0;
        virtual void PreRender() = 0;
        virtual void SceneRender(float delta_time) = 0;
        virtual void PostRender() = 0;
        virtual void Terminate() = 0;
        virtual void ProcessInput(GLFWwindow* window, float delta_time) = 0;

        // Current values of the mouse position
        float mouse_pos_x_;
        float mouse_pos_y_;

        // Previous values of the mouse position
        float prev_mouse_pos_x_;
        float prev_mouse_pos_y_;

        // Returns true when the mouse first enters the window
        bool bMouseIn_;
        
    protected:
        UWindow *window_;
        std::unique_ptr<Scene> scene_;
};
