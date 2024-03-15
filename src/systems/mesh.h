#pragma once
#include "../resources/shader.h"
#include "buffer_geometry.h"
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

#include "bounding_box.h"
template <typename T>
class UMesh {
    public:
        virtual void Draw(float &delta_time) = 0;
        Transforms transforms_;
        Shader* shader_;
        virtual void ComputeBoundingBox(Shader* shader, T vertices_data = {}) = 0;
    protected:
        BoundingBox* bounding_box;
};