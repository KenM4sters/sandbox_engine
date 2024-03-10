#pragma once
#include "../../utils/includes.h"
#include "../../resources/texture.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

class ModelMesh {
    public:
        ModelMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures) {
            vertices_ = vertices;
            indices_ = indices;
            textures_ = textures;
        }

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<Texture2D> textures_;
        unsigned int VAO_;
    private:
        unsigned int VBO_, EBO_;
};