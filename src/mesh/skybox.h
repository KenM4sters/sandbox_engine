#include "../utils/includes.h"
#include "../resources/shader.h"
#include "../resources/stb_image.h"
#include "../camera/camera.h"


struct Transforms {
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
        ~Skybox() {}
        void DrawCube();
    private:
        std::vector<std::string> face_textures_;
        std::vector<float> vertices_;
        unsigned int VAO_, VBO_;
        Tex* tex_;
        Shader* shader_;
        Transforms transforms_;
        Camera* camera_;
        unsigned int* LoadCubeMap() const;
        void InitCube(); 
};