#pragma once
#include "buffer_geometry.h"
#include "../resources/shader.h"
#include "../resources/texture.h"

struct Rotation {
    float rotation_angle{0.0f};
    glm::vec3 rotation_axis{0.0f, 1.0f, 0.0f};
};

struct Transforms {
    glm::vec3 position{0.0f, 0.0f, -5.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    Rotation rotation;
    glm::mat4 model;
};

struct Material {
    glm::vec3 ambient{0.2f, 0.2f, 0.2f};
    std::vector<Texture2D*> textures;
    glm::vec3 specular{0.2f, 0.2f, 0.2f};
    float shininess{10.0f};
};

class BasicMesh {
    public:
        BasicMesh(BufferGeometry* geometry, Shader* shader, Texture2D* texture)
            : geometry_(geometry), shader_(shader) 
        {
            mat_.textures.push_back(texture);
        }
        BasicMesh(BufferGeometry* geometry, Shader* shader, std::vector<Texture2D*> &textures)
            : geometry_(geometry), shader_(shader) 
        {
            mat_.textures = textures;
        }
        ~BasicMesh() {}
        void DrawMesh();
                
        Transforms transforms_;
        Shader* shader_;
        Material mat_;
    private:
        BufferGeometry* geometry_;
        void InitMesh();
};