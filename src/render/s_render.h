#pragma once
#include "render.h"

// Header for rendering

namespace sandbox_render {
    class SRenderer : public URenderer {
        public:
            void init(sandbox_window::UWindow *window) override;
            void PreRender() override;
            void PostRender() override;
            void Terminate() override;
    };
}