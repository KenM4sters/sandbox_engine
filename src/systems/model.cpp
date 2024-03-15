#include "model.h"

void Model::DrawModel() {
    auto transforms = *transforms_;
    for(auto& m : meshes_) {
        m.transforms_ = transforms;
        m.Draw();
        bounding_box_->Draw();
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
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(ProcessModelMesh(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }

}   

StandardMesh Model::ProcessModelMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D> textures;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 p_vector;
        p_vector.x = mesh->mVertices[i].x;
        p_vector.y = mesh->mVertices[i].y;
        p_vector.z = mesh->mVertices[i].z;
        vertex.position = p_vector;

        // Computing Bounding Box
        // Checking whether the vertices are more extreme than the previously stored vertices.
        // ----------------------------------------------------------------
        if(p_vector.x > vertex_ranges_.maxima.x) vertex_ranges_.maxima.x = p_vector.x;
        if(p_vector.x < vertex_ranges_.minima.x) vertex_ranges_.minima.x = p_vector.x;

        if(p_vector.y > vertex_ranges_.maxima.y) vertex_ranges_.maxima.y = p_vector.y;
        if(p_vector.y < vertex_ranges_.minima.y) vertex_ranges_.minima.y = p_vector.y;

        if(p_vector.z > vertex_ranges_.maxima.z) vertex_ranges_.maxima.z = p_vector.z;
        if(p_vector.z < vertex_ranges_.minima.z) vertex_ranges_.minima.z = p_vector.z;
        // ----------------------------------------------------------------

        if(mesh->HasNormals()) {
            p_vector.x = mesh->mNormals[i].x;
            p_vector.y = mesh->mNormals[i].y;
            p_vector.z = mesh->mNormals[i].z;
            vertex.normal = p_vector;
        }
        if(mesh->mTextureCoords[0]) {
            glm::vec2 p;
            p.x = mesh->mTextureCoords[0][i].x;
            p.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = p;

            p_vector.x = mesh->mTangents[i].x;
            p_vector.y = mesh->mTangents[i].y;
            p_vector.z = mesh->mTangents[i].z;
            vertex.tangent = p_vector;
            // bitangent
            p_vector.x = mesh->mBitangents[i].x;
            p_vector.y = mesh->mBitangents[i].y;
            p_vector.z = mesh->mBitangents[i].z;
            vertex.bi_tangent = p_vector;
        } else {
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture2D> diffuseMaps = LoadModelTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture2D> specularMaps = LoadModelTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture2D> normalMaps = LoadModelTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture2D> heightMaps = LoadModelTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


    BufferGeometry geo = BufferGeometry(vertices, indices);
    return StandardMesh(geo, shader_, textures);
}

std::vector<Texture2D> Model::LoadModelTextures(aiMaterial* mat, aiTextureType type, std::string type_name) {
    std::vector<Texture2D> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        auto str_c = str.C_Str();
        if(!textures_loaded_.count(str_c)) {
            Texture2D texture(SANDBOX_OBJECT, type_name);
            texture.LoadFromFile(str_c, dir_);
            textures.push_back(texture);
            textures_loaded_[str_c] = texture;
        } else {
            textures.push_back(textures_loaded_[str_c]);
        }
    }
    return textures;
}

void Model::ComputeBoundingBox() {
    // Apply effects of all transformations (if none were applied, then they'll be unchanged).
    // ----------------------------------------------
    vertex_ranges_.maxima.x *= transforms_->scale.x;
    vertex_ranges_.maxima.y *= transforms_->scale.y;
    vertex_ranges_.maxima.z *= transforms_->scale.z;

    vertex_ranges_.minima.x *= transforms_->scale.x;
    vertex_ranges_.minima.y *= transforms_->scale.y;
    vertex_ranges_.minima.z *= transforms_->scale.z;
    // ----------------------------------------------

    // creating name aliases to make the following vertices more readable.
    auto& min_x = vertex_ranges_.minima.x;
    auto& min_y = vertex_ranges_.minima.y;
    auto& min_z = vertex_ranges_.minima.z;

    auto& max_x = vertex_ranges_.maxima.x;
    auto& max_y = vertex_ranges_.maxima.y;
    auto& max_z = vertex_ranges_.maxima.z;

    // You see includes.h for the positions coords of a uniform cube for reference.
    const std::vector<float> vertices = {
      //  back
        min_x, min_y,  min_z, 0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        max_x, min_y,  min_z, 0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        max_x, max_y,  min_z, 0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        max_x, max_y,  min_z, 0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        min_x, max_y,  min_z, 0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        min_x, min_y,  min_z, 0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
      // front
        max_x, min_y,  max_z, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        max_x, min_y,  max_z, 0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        max_x, max_y,  max_z, 0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        max_x, max_y,  max_z, 0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        min_x, max_y,  max_z, 0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        min_x, min_y,  max_z, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
      // left
        min_x, max_y, max_z, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        min_x, max_y, min_z, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        min_x, min_y, min_z, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        min_x, min_y, min_z, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        min_x, min_y, max_z, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        min_x, max_y, max_z, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      // right
        max_x, max_y, max_z,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        max_x, max_y, min_z,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        max_x, min_y, min_z,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        max_x, min_y, min_z,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        max_x, min_y, max_z,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        max_x, max_y, max_z,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
      // bottom
        min_x, min_y, min_z,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        max_x, min_y, min_z,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        max_x, min_y, max_z,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        max_x, min_y, max_z,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        min_x, min_y, max_z,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        min_x, min_y, min_z,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
      // top
        min_x, max_y, min_z,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        max_x, max_y, min_z,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        max_x, max_y, max_z,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        max_x, max_y, max_z,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        min_x, max_y, max_z,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        min_x, max_y, min_z,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    bounding_box_ = new BoundingBox(bounding_box_shader_, transforms_, vertices);
}
