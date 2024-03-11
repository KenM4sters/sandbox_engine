#pragma once
#include "../utils/includes.h"
#include "../resources/s_shader_resource.h"
#include "../resources/s_texture_resource.h"
#include "../mesh/mesh.h"
#include "../camera/camera.h"
#include "../mesh/skybox.h"
// Scene class which is responsible for creating and rendering our main scene
class Scene  {
    public:
        Scene(unsigned int w, unsigned int h, Camera* camera);
        ~Scene();
        // Initializes all game objects (meshes) 
        void Init();
        // Adds mesh to an unordered_map of meshes that is traversed in the Render()
        void AddGameObject(Mesh* mesh, std::string name);
        void AddLight(Mesh* mesh, std::string name);
        std::unordered_map<std::string, Mesh*>* GetMeshRepo() {return &game_objects_;}
        std::unordered_map<std::string, Mesh*>* GetLights() {return &lights_;}
        void Render(float &delta_time);
        
    private:
        Camera* camera_;
        Skybox* skybox_;
        std::unique_ptr<SShaderResource> shader_res_;
        std::unique_ptr<STextureResource> texture_res_;
        std::unordered_map<std::string, Mesh*> game_objects_;
        std::unordered_map<std::string, Mesh*> lights_;
        unsigned int scr_width_, scr_height_;
};