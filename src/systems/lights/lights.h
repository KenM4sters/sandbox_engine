#pragma once
#include "../../utils/includes.h"
#include "../../resources/s_shader_resource.h"
#include "../../resources/s_texture_resource.h"
#include "../basic_mesh.h"
#include "../base_system.h"


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
        SShaderResource* SetLightData();
    private:
        SShaderResource objects_shaders_;

};