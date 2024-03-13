#pragma once
#include "../utils/includes.h"
#include "../resources/shader.h"
#include "../resources/texture.h"
#include "../resources/s_shader_resource.h"
#include "../resources/s_texture_resource.h"
#include "basic_mesh.h"


class URenderSystem {
    public:
        URenderSystem(SShaderResource* shaders, STextureResource* textures)
            : shaders_(shaders), textures_(textures)
        {
        }
    protected:
        SShaderResource* shaders_;
        STextureResource* textures_;
        std::unordered_map<std::string, BasicMesh*> children_;
};  
