#pragma once
#include "../utils/includes.h"
#include "system_includes.h"
#define MAX_BONE_INFLUENCE 4



class BufferGeometry {
    public:
        // Takes in a vector Vertex structs (used mostly for model loading).
        BufferGeometry(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) 
            : vertices_vertex(vertices), indices_(indices) {
            InitGeometry();
        }
        // Takes in a simple vector of floats (used for simple shape loading).
        BufferGeometry(const std::vector<float> &vertices, unsigned int vertex_count);
        // Similar to the above only with the addition of an indices container.
        BufferGeometry(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, unsigned int vertex_count);
        ~BufferGeometry() {}
        void DrawGeometry();
        // Function to draw elements with a specified number of elements and offset into the element buffer.
        void DrawGeometry(unsigned int n_strips, unsigned int n_vertices_strip);
    private:
        void InitGeometry();
        const std::vector<Vertex> vertices_vertex;
        const std::vector<float> vertices_float;
        const std::vector<unsigned int> indices_;
        unsigned int VAO_, VBO_, EBO_;
        unsigned int vertex_count_;
};


