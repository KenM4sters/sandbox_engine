#pragma once 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "standard_mesh.h"
#include "../utils/includes.h"

class Model {
    public:
        Model(const std::string &path, Shader* shader) : shader_(shader) {
            LoadModel(path);
        }
        ~Model() {}
        void DrawModel();
        void LoadModel(const std::string &path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        std::vector<Texture2D> LoadModelTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
        StandardMesh ProcessModelMesh(aiMesh *mesh, const aiScene *scene);
        Transforms transforms_;
    private:
        std::vector<StandardMesh> meshes_;
        std::unordered_map<std::string, Texture2D> textures_loaded_;
        Shader* shader_;
        std::string dir_;
        bool bGammeCorrection;
};