#pragma once 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "standard_mesh.h"
#include "../utils/includes.h"

class Model {
    public:
        Model(const std::string &path, Shader &shader) {
            LoadModel(path);
        }
        ~Model() {}
        void DrawModel();
        void LoadModel(const std::string &path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        void ProcessModelMesh();
    private:
        std::vector<StandardMesh> meshes_;
        std::unordered_map<std::string, Texture2D> textures_loaded_;
        std::string dir_;
        bool bGammeCorrection;

};