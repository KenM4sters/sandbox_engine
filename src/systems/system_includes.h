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
    glm::vec3 position{0.0f, 0.0f, -5.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    Rotation rotation;
    glm::vec3 velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 accelration{0.0f, 0.0f, 0.0f};
    glm::mat4 model;
};

struct Material {
    glm::vec3 ambient{0.2f, 0.2f, 0.2f};
    std::vector<Texture2D*> textures;
    glm::vec3 specular{0.2f, 0.2f, 0.2f};
    float shininess{10.0f};
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal{0.0f, 1.0f, 0.0f};   // Normals are required for calculating phong shading due to lights in the scene.
    glm::vec2 tex_coords;
    // Model Specifcs
    glm::vec3 tangent;
    glm::vec3 bi_tangent;
};

struct TerrainQuadrant {
    std::vector<Vertex> vertices;
    glm::vec3 center_vert;
    glm::vec3 left, right, top, bottom;
};