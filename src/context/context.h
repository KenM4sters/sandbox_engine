#pragma once
#include "../window.h"
#include "../scene/scene.h"
#include "post_processing.h"
#include "interface.h"

// Base class for rendering our scene based one whether PostProcessing is enabled or not. 

class UContext {
    public:
        UContext() : window_(nullptr) {
                scene_ = nullptr;
                fbo_shader_res_ = nullptr;
                fbo_shader_ = nullptr;
            }
        virtual void Init(UWindow *window) = 0;
        virtual void Terminate() = 0;
        virtual void ProcessInput(GLFWwindow* window, float delta_time) = 0;
        virtual void Render(float delta_time) = 0;
        
    protected:
        virtual void PreRender() = 0;
        virtual void SceneRender(float delta_time) = 0;
        virtual void PostRender() = 0;
        virtual void RenderWithPostProcessing(Shader* shader, PostProcessing* post_processing, float delta_time) = 0;
        virtual void RenderWithoutPostProcessing(float delta_time) = 0;
        UWindow* window_;
        UserInterface* interface_;
        std::unique_ptr<Scene> scene_;
        CollisionHandler* collision_handler_;
        Shader* fbo_shader_; 
        PostProcessing* post_processing_;
        SShaderResource* fbo_shader_res_;
        bool bPostProcessingEnabled;
};
