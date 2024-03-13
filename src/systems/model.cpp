#include "model.h"

void Model::DrawModel() {
    for(auto& m : meshes_) {
        m.Draw();
    }
}

void Model::LoadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    dir_ = path.substr(0, path.find_last_of("/")); // Generates path from root dir to where the model is saved.

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {

}   

void Model::ProcessModelMesh() {

}
