#pragma once
#include "buffer_geometry.h"
#include "../resources/shader.h"
#include "../resources/texture.h"

struct Transforms {
    glm::vec3 position{0.0f, 0.0f, -5.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 rotation_axis{0.0f, 1.0f, 0.0f};
    float rotation_angle{0.0f};
    glm::mat4 model;
};

struct Material {
    glm::vec3 ambient{1.0f, 0.0f, 0.0f};
    Texture2D* texture;
    glm::vec3 specular{1.0f, 1.0f, 1.0f};
    float shininess{32.0f};
};

class Mesh {
    public:
        Mesh(BufferGeometry* geometry, Shader* shader, Texture2D* texture)
            : geometry_(geometry), shader_(shader) {
                mat_.texture = texture;
            }
        ~Mesh() {}
        void DrawMesh();
                
        Transforms transforms_;
        Shader* shader_;
        Material mat_;
    private:
        BufferGeometry* geometry_;
        void InitMesh();
};