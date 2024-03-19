#pragma once
#include "../../utils/includes.h"
#include "../../resources/shader.h"
#include "../../resources/stb_image.h"
#include "../../camera/camera.h"

/**
 * The Skybox class handles the creation of the skybox that you can see in the scene - in many ways,
 * it's similar to the Standard and Basic Mesh classes, but different enough in its transforms and texture
 * data to deserve its own class. Skybox's aren't rendered in the same way as other objects, since they
 * don't require any model matrix and have different projection and view matrices to make sure that
 * the camera can't eventually go through the skybox.
*/

struct SkyboxTransforms {
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 translation;
    glm::mat4 projection;
    glm::mat4 view;
};

struct Tex {
    unsigned int ID;
    std::string name;
};

class Skybox {
    public:
        Skybox(std::vector<float> vertices, std::vector<std::string> face_textures, Shader* shader, Camera* camera );
        ~Skybox() {
            delete tex_;
        }
        // Renders the skybox to the screen.
        void DrawCube();
    private:
        std::vector<std::string> face_textures_;
        std::vector<float> vertices_;
        unsigned int VAO_, VBO_;
        Tex* tex_;
        Shader* shader_;
        SkyboxTransforms transforms_;
        Camera* camera_;
        // Loads texture data for the skybox faces
        unsigned int* LoadCubeMap() const;
        // allocates memory for cube vertex data
        void InitCube(); 
};