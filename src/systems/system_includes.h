#pragma once
#include "../utils/includes.h"
#include "../resources/texture.h"

struct BoundingBoxSizes {
    float width, height, depth;
};

struct Rotation {
    float rotation_angle{0.0f};
    glm::vec3 rotation_axis{0.0f, 1.0f, 0.0f};
};

struct Transforms {
    // Initially set to {0.0f, 2.0f, 0.0f}
    glm::vec3 position{0.0f, 2.0f, 0.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    Rotation rotation;
    glm::vec3 velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 accelration{0.0f, 0.0f, 0.0f};
    glm::mat4 model;
};

struct Material {
    glm::vec3 ambient{0.4f, 0.4f, 0.4f};
    std::vector<Texture2D*> textures;
    glm::vec3 specular{0.1f, 0.1f, 0.1f};
    float shininess{10.0f};
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal{0.0f, 1.0f, 0.0f};   // Normals are required for calculating phong shading due to lights in the scene.
    glm::vec2 tex_coords;
    // Model Specifcs
    glm::vec3 tangent;
    glm::vec3 bi_tangent;
    // Terrain specifics
    float texel_val{0.0f};
};

struct VertexQuadrant {
    std::vector<Vertex> vertices;
    glm::vec3 center_vert;
    glm::vec3 left, right, top, bottom;
};

struct TerrainQuadrant {
    int max_w, max_d;
};