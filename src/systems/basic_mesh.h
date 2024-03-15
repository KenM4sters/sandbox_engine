#pragma once
#include "mesh.h"

class BasicMesh : public UMesh<float> {
    public:
        BasicMesh(BufferGeometry* geometry, Shader* shader, Texture2D* texture)
            : geometry_(geometry) 
        {
            shader_ = shader;
            mat_.textures.push_back(texture);
        }
        BasicMesh(BufferGeometry* geometry, Shader* shader, std::vector<Texture2D*> &textures)
            : geometry_(geometry) 
        {
            shader_ = shader;
            mat_.textures = textures;
        }
        ~BasicMesh() {}
        void Draw(float &delta_time) override;
        void ComputeBoundingBox(Shader* shader, float vertices_data = 0.0f) override;
            
        Material mat_;
    private:
        BufferGeometry* geometry_;
};