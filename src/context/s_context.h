#pragma once
#include "context.h"

/**
 * SContext handles intiating and rendering our scene, with or without posprocessing. 
*/

class SContext : public UContext {
    public:
        SContext(bool bPostProcessing);
        ~SContext() {
            #ifdef SANDBOX_DEBUG 
                std::cout << "SContext is being destroyed!" << std::endl;
            #endif
        }
        void Init(UWindow *window) override;
        // Render() is called by the window and either calls RenderWithPostProcessing() or RenderWithoutPostProcessing() based
        // on the value of bPostProcessing, a boolean member of UContext.
        void Render(float delta_time) override;
        // Sets the window's background color.
        void PreRender() override;
        void SceneRender(float delta_time) override;
        void PostRender() override;
        // Changes the order of rendering our scene so that it renders to a custom framebuffer
        // defined in PostProcessing.
        void RenderWithPostProcessing(Shader* shader, PostProcessing* post_processing, float delta_time) override;
        void RenderWithoutPostProcessing(float delta_time) override;
        void Terminate() override;
        // Handles camera input.
        void ProcessInput(GLFWwindow* window, float delta_time) override;
};
