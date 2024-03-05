#pragma once
#include "../window.h"
#include "../scene/scene.h"

// Base class for rendering 

class UContext {
    public:
        UContext() : window_(nullptr), scene_(nullptr) {}

        virtual void init(UWindow *window) = 0;
        virtual void PreRender() = 0;
        virtual void SceneRender() = 0;
        virtual void PostRender() = 0;
        virtual void Terminate() = 0;


    protected:
        UWindow *window_;
        std::unique_ptr<Scene> scene_;

};
