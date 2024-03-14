#pragma once
#include "../utils/includes.h"
#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;   // Normals are required for calculating phong shading due to lights in the scene.
    glm::vec2 tex_coords;
    // Model Specifcs
    glm::vec3 tangent;
    glm::vec3 bi_tangent;
    int n_model_bones[MAX_BONE_INFLUENCE];
    float model_weights[MAX_BONE_INFLUENCE];
};

class BufferGeometry {
    public:
        // Takes in a vector Vertex structs (used mostly for model loading).
        BufferGeometry(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) 
            : vertices_vertex(vertices), indices_(indices) {
            InitGeometry();
        }
        // Takes in a simple vector of floats (used for simple shape loading).
        BufferGeometry(std::vector<float> &vertices, unsigned int vertex_count);
        ~BufferGeometry() {}
        void DrawGeometry();
    private:
        void InitGeometry();
        std::vector<Vertex> vertices_vertex;
        std::vector<float> vertices_float;
        std::vector<unsigned int> indices_;
        unsigned int VAO_, VBO_, EBO_;
        unsigned int vertex_count_;
};


