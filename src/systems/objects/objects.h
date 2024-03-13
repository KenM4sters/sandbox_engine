#pragma once
#include "../base_system.h"


class SObjects : URenderSystem {
    public:
        SObjects(SShaderResource* shaders, STextureResource* textures) 
            : URenderSystem(shaders, textures) 
        {
            Init();
        }
        ~SObjects() {}
        void Init();
        void Draw();
    private:
};