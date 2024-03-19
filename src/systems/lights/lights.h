#pragma once
#include "../../utils/includes.h"
#include "../../resources/s_shader_resource.h"
#include "../../resources/s_texture_resource.h"
#include "../basic_mesh.h"
#include "../base_system.h"

/**
 * SLights is one of two main render systems that handles storing BasicMesh, StandardMesh, Model etc.. objects
 * in an unordered_map, and calling each of their draw functions.
*/

class SLights : URenderSystem {
    public:
        SLights(SShaderResource* shaders, STextureResource* textures, CollisionHandler* collision_handler) 
            : URenderSystem(shaders, textures, collision_handler_) 
        {
        }
        ~SLights() {}
        void Init() override;
        void Draw(float &delta_time) override;
        void UpdateLights();
        // SetLightData() is a function unique to SLights which returns the shaders belonging to the 
        // SObjects class. While perhaps seeming strange at first, all object shaders need to be set with 
        // information about the whereabouts of all lights as well as their specific material data, so all
        // shaders are first passed to Slights before SObjects. 
        SShaderResource* SetLightData();
    private:
        SShaderResource objects_shaders_;

};