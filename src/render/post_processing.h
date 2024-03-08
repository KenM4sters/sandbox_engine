#pragma once 
#include "../utils/includes.h"
#include "../resources/shader.h"
#include "../resources/texture.h"

class PostProcessing {
    public:
        unsigned int width_, height_;
        Texture2D tex_;
        Shader* shader_;
        PostProcessing(unsigned int width, unsigned int height, Shader* shader);
        void BeginRender(); 
        void EndRender();
        void RenderQuad();

    private:
        unsigned int FBO_;
        unsigned int VAO_;
        unsigned int RBO_;
        void InitQuad(); 

};