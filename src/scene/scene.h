#pragma once
#include "../utils/includes.h"
#include "../resources/s_shader_resource.h"
// Scene class which is responsible for creating and rendering our main scene
class Scene  {
    public:
        Scene();
        ~Scene();
        void Init();
        void Render();
    private:
        std::unique_ptr<SShaderResource> shader_res_;
        unsigned int VAO_, VBO_;
};