#pragma once
#include "mesh.h"

/**
 * The StandardMesh class is very similar to its sister class, BasicMesh, only its Draw function
 * expects the texture data arranged in a way that supports external model loading.
 * It expects the textures have either a diffuse, specular, normal or height type which sometimes 
 * is a bit unecessary for simple objects, hence the abstraction. 
 * 
 * Please see basic_mesh.h for specifics on its methods.
*/

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