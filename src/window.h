#pragma once
#include "utils/includes.h"

// Base class for window

class UWindow {
    public:
        virtual void* GetNativeWindow() = 0;
        virtual void SetNativeWindow(void* window) = 0;

        virtual void HandleKeyInput(int key, int scancode, int action, int mods) = 0;
        virtual void HandleWindowResize(int w, int h) = 0;

        int width_, height_;
        std::string title_;
};