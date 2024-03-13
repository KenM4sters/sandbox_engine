#pragma once
#include "../base_system.h"
#include "../../utils/includes.h"
#include "../mesh.h"
#include "../../resources/s_shader_resource.h"
#include "../../resources/s_texture_resource.h"


class SLights : URenderSystem {
    public:
        SLights(SShaderResource* shaders, STextureResource* textures) 
            : URenderSystem(shaders, textures) 
        {
        }
        ~SLights() {}
        void Draw();
        void Init();
        SShaderResource* SetLightData();
    private:
        SShaderResource objects_shaders_;

};