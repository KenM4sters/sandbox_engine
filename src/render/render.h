#pragma once
#include "../window/s_window.h"

// Base class for rendering 

namespace sandbox_render {
    class URenderer {
        public:
            URenderer() : window_(nullptr) {}
            ~URenderer() {}

            virtual void init(sandbox_window::UWindow *window) {
                window_ = window;
            }
            virtual void PreRender() = 0;
            virtual void PostRender() = 0;
            virtual void Terminate() = 0;


        protected:
            sandbox_window::UWindow *window_;
   };
}