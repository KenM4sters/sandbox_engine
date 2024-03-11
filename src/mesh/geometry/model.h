#pragma once
#include "../../utils/includes.h"
#include "../../resources/texture.h"
#include "../../resources/shader.h"
#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class ModelGeometry {
    public:
        ModelGeometry(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
            vertices_ = vertices;
            indices_ = indices;
            textures_ = textures;
            Init();
        }
        void Init();
        void Draw(Shader& shader);

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<Texture> textures_;
        unsigned int VAO_;
    private:
        unsigned int VBO_, EBO_;
};