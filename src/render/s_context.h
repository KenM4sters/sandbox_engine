#pragma once
#include "context.h"

// Header for rendering
class SContext : public UContext {
    public:
        SContext(bool bPostProcessing);
        void Init(UWindow *window) override;
        void Render(float delta_time) override;
        void PreRender() override;
        void SceneRender(float delta_time) override;
        void PostRender() override;
        void RenderWithPostProcessing(Shader* shader, std::unique_ptr<PostProcessing> post_processing, float delta_time) override;
        void RenderWithoutPostProcessing(float delta_time) override;
        void Terminate() override;
        void ProcessInput(GLFWwindow* window, float delta_time) override;
};
