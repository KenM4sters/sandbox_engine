#include "./geometry/model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../resources/stb_image.h"


unsigned int LoadTextureFromFile(const char* path, const std::string& dir, bool gamma);

class Model {
    public:
        std::vector<ModelGeometry> model_geometries_;
        std::vector<Texture> textures_loaded_;
        std::string dir_;
        bool bGammeCorrection;

        Model(std::string const &path, bool gamma = false);
        void Draw(Shader& shader) {
            for(auto& model : model_geometries_) {
                model.Draw(shader);
            }
        }
    private:
        void LoadModel(std::string const &path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        ModelGeometry ProcessGeometry(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
};

unsigned int LoadTextureFromFile(const char* path, const std::string& dir, bool gamma = false) {
    std::string filename = static_cast<std::string>(path);
    filename = dir + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}