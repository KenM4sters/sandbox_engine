#pragma once 
#include "../utils/includes.h"
#include "../resources/shader.h"
#include "../resources/s_shader_resource.h"
#include "../resources/texture.h"

class PostProcessing {
    public:
        ~PostProcessing() {
            #ifdef SANDBOX_DEBUG 
                std::cout << "PostProcessing is being destroyed!" << std::endl;
            #endif
        }
        unsigned int width_, height_;
        Texture2D tex_ = Texture2D(SANDBOX_OBJECT);
        Shader* shader_;
        PostProcessing(unsigned int width, unsigned int height, SShaderResource* shader);
        void BeginRender(); 
        void EndRender();
        void RenderQuad();

    private:
        unsigned int FBO_, VAO_, RBO_;
        void InitQuad(); 

};