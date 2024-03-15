#pragma once
#include "../base_system.h"
#include "../model.h"


class SObjects : URenderSystem {
    public:
        SObjects(SShaderResource* shaders, STextureResource* textures, CollisionHandler* collision_handler) 
            : URenderSystem(shaders, textures, collision_handler_) 
        {
            Init();
        }
        ~SObjects() {}
        void Init() override;
        void Draw(float &delta_time) override;
    private:
        std::unordered_map<std::string, Model*> models_;
};