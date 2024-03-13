#pragma once
#include "../utils/includes.h"
#include "../resources/s_shader_resource.h"
#include "../resources/s_texture_resource.h"
#include "../camera/camera.h"
#include "../systems/lights/lights.h"
#include "../systems/objects/objects.h"
#include "../systems/skybox/skybox.h"
// Scene class which is responsible for creating and rendering our main scene
class Scene  {
    public:
        Scene(unsigned int w, unsigned int h, Camera* camera);
        ~Scene() {}
        // Initializes all game objects (meshes) 
        void Init();
        void Render(float &delta_time);
        void SetCameraData(Camera* camera);
        
    private:
        Camera* camera_;
        SShaderResource shader_res_;
        STextureResource texture_res_;
        SLights* lights_res_;
        SObjects* objects_res_;
        Skybox* skybox_;
        unsigned int scr_width_, scr_height_;
};