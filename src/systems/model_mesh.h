#pragma once
#include "buffer_geometry.h"
#include "../resources/shader.h"
#include "../resources/texture.h"


class ModelMesh {
    public:
        ModelMesh(BufferGeometry* geometry, std::vector<Texture2D*> &textures)
            : geometry_(geometry), textures_(textures)
        {}
        void Draw(Shader& shader);
    private:
        std::vector<Texture2D*> textures_;
        BufferGeometry* geometry_;

};