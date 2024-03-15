#pragma once
#include "../utils/includes.h"
#include "../resources/shader.h"
#include "../resources/texture.h"
#include "../resources/s_shader_resource.h"
#include "../resources/s_texture_resource.h"
#include "basic_mesh.h"
#include "../context/collision_handler.h"
#include "../world_physics/physics.h"


class URenderSystem {
    public:
        URenderSystem(SShaderResource* shaders, STextureResource* textures, CollisionHandler* collision_handler)
            : shaders_(shaders), textures_(textures), collision_handler_(collision_handler)
        {
        }
        virtual void Init() = 0;
        virtual void Draw(float &delta_time) = 0;
    protected:
        SShaderResource* shaders_;
        STextureResource* textures_;
        std::unordered_map<std::string, BasicMesh*> children_;
        CollisionHandler* collision_handler_;
        
};  
