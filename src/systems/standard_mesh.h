#pragma once
#include "mesh.h"

class StandardMesh : public UMesh {
    public:
        StandardMesh(BufferGeometry &geometry, Shader* shader, std::vector<Texture2D> &textures)
            : geometry_(geometry), textures_(textures)
        {
            shader_ = shader;
        }
        void Draw() override;
        void ComputeBoundingBox(Shader* shader) override;
    private:
        BufferGeometry geometry_;
        std::vector<Texture2D> textures_;

};