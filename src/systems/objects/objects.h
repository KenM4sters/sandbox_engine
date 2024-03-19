#pragma once
#include "../base_system.h"
#include "../model.h"

/**
 * SObjects is one of two main render systems that handles storing BasicMesh, StandardMesh, Model etc.. objects
 * in an unordered_map, and calling each of their draw functions.
*/


class SObjects : URenderSystem {
    public:
        SObjects(SShaderResource* shaders, STextureResource* textures, CollisionHandler* collision_handler) 
            : URenderSystem(shaders, textures, collision_handler_) 
        {
            Init();
        }
        ~SObjects() {}
        void Init() override;
        // call Draw functions of each item in models_
        void Draw(float &delta_time) override;
    private:
        std::unordered_map<std::string, Model*> models_;
};