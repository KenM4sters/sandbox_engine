#pragma once
#include "../utils/includes.h"
#include "../resources/s_shader_resource.h"
#include "../mesh/mesh.h"
// Scene class which is responsible for creating and rendering our main scene
class Scene  {
    public:
        Scene();
        ~Scene();
        void Init();
        void AddMesh(Mesh* mesh, std::string& name);
        void Render();
    private:
        std::unique_ptr<SShaderResource> shader_res_;
        std::unordered_map<std::string, Mesh*> mesh_repo_;
        unsigned int VAO_, VBO_;
};