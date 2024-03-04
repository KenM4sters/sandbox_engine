#pragma once
#include "render.h"

// Header for rendering

namespace sandbox_render {
    class SRenderer : public URenderer {
        void init(sandbox_window::SWindow *window) override;
        void PreRender() override;
        void PostRender() override;
        void Terminate() override;
    };
}