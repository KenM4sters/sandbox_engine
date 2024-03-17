#pragma once
#include "mesh.h"

struct VertexRanges {
    glm::vec3 maxima = glm::vec3(0.0f);
    glm::vec3 minima = glm::vec3(0.0f);
};

class StandardMesh : public UMesh<VertexRanges> {
    public:
        StandardMesh(BufferGeometry &geometry, Shader* shader, std::vector<Texture2D> &textures)
            : geometry_(geometry), textures_(textures)
        {
            shader_ = shader;
        }
        void Draw(float &delta_time) override;
        void DrawInstanced(float &delta_time, unsigned int instance_count) override {}
        void ComputeBoundingBox(Shader* shader, VertexRanges vertices_data = {}) override {}
    private:
        BufferGeometry geometry_;
        std::vector<Texture2D> textures_;

};