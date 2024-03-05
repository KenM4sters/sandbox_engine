#pragma once
#include "context.h"

// Header for rendering
class SContext : public UContext {
    public:
        void init(UWindow *window) override;
        void PreRender() override;
        void SceneRender() override;
        void PostRender() override;
        void Terminate() override;
};
