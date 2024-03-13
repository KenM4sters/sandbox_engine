#pragma once
#include "buffer_geometry.h"
#include "../resources/shader.h"
#include "../resources/texture.h"


class StandardMesh {
    public:
        StandardMesh(BufferGeometry* geometry, Shader &shader, std::vector<Texture2D*> &textures)
            : geometry_(geometry), textures_(textures), shader_(shader)
        {}
        void Draw();
    private:
        std::vector<Texture2D*> textures_;
        Shader shader_;
        BufferGeometry* geometry_;

};