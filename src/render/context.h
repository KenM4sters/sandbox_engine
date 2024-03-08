#pragma once
#include "../window.h"
#include "../scene/scene.h"
#include "post_processing.h"

// Base class for rendering 

class UContext {
    public:
        UContext() : window_(nullptr) {scene_ = nullptr;}

        virtual void Init(UWindow *window) = 0;
        virtual void PreRender() = 0;
        virtual void SceneRender(float delta_time) = 0;
        virtual void PostRender() = 0;
        virtual void RenderWithPostProcessing(Shader* shader, std::unique_ptr<PostProcessing> post_processing, float delta_time) = 0;
        virtual void Terminate() = 0;
        virtual void ProcessInput(GLFWwindow* window, float delta_time) = 0;
        
    protected:
        UWindow *window_;
        std::unique_ptr<Scene> scene_;
};
