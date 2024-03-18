#pragma once 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../utils/includes.h"
#include "standard_mesh.h"

class Model {
    public:
        Model(const std::string &path, Shader* shader, Shader* bounding_box_shader) 
            : shader_(shader), bounding_box_shader_(bounding_box_shader) 
        {
            LoadModel(path);
        }
        ~Model() { std::cout << "model is destroyed" << std::endl; }
        void DrawModel(float &delta_time);
        void LoadModel(const std::string &path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        std::vector<Texture2D> LoadModelTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
        StandardMesh ProcessModelMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<StandardMesh> GetMeshes() const {
            return meshes_;
        }
        void ComputeBoundingBox();
        Transforms* transforms_ = new Transforms();
    private:
        std::vector<StandardMesh> meshes_;
        std::unordered_map<std::string, Texture2D> textures_loaded_;
        VertexRanges vertex_ranges_;
        Shader* shader_;
        Shader* bounding_box_shader_;
        std::string dir_;
        bool bGammeCorrection;
        BoundingBox* bounding_box_ = nullptr;
};