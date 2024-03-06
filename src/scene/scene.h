#pragma once
#include "../utils/includes.h"
#include "../resources/s_shader_resource.h"
#include "../mesh/mesh.h"
#include "../camera/camera.h"
// Scene class which is responsible for creating and rendering our main scene
class Scene  {
    public:
        Scene(unsigned int w, unsigned int h);
        ~Scene();
        void Init();
        void AddMesh(Mesh* mesh, std::string name);
        void Render(float &delta_time);
        
        std::unique_ptr<Camera> camera_;
    private:
        
        std::unique_ptr<SShaderResource> shader_res_;
        std::unordered_map<std::string, Mesh*> mesh_repo_;
        unsigned int VAO_, VBO_;
        unsigned int scr_width_, scr_height_;
};