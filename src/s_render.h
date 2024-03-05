#pragma once
#include "render.h"

// Header for rendering
class SRenderer : public URenderer {
    public:
        void init(UWindow *window) override;
        void PreRender() override;
        void PostRender() override;
        void Terminate() override;
};
