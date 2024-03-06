#pragma once
#include "context.h"

// Header for rendering
class SContext : public UContext {
    public:
        void init(UWindow *window) override;
        void PreRender() override;
        void SceneRender(float delta_time) override;
        void PostRender() override;
        void Terminate() override;
        void ProcessInput(GLFWwindow* window, float delta_time) override;
};
