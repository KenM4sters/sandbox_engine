#include "terrain.h"

void Terrain::InitTerrainMeshData(unsigned char* data, int &width, int &height, int &nr_channels) {
    // These two variables will be used later to generate indices for our terrain mesh data.
    n_strips_ = height - 1;
    n_vertices_strip_ = width * 2;
    std::cout << height << std::endl;
    std::cout << width << std::endl;

    // Vertices
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {

            unsigned char* texel = data + (j + width * i) * nr_channels;
            unsigned char y_displacement = texel[0];
            Vertex v;
            v.position.x = -(height/2.0f) + i;
            v.position.y = (int)y_displacement * y_scale_ / 255;
            v.position.z = -(width/2.0f) + j;

            v.tex_coords.x = (float)i/height;
            v.tex_coords.y = (float)j/width;

            v.tangent.x = 0.0f;
            v.tangent.y = 0.0f;
            v.tangent.z = 0.0f;

            v.bi_tangent.x = 0.0f;
            v.bi_tangent.y = 0.0f;
            v.bi_tangent.z = 0.0f;

            vertices_.push_back(v);
        }
    }

    // Normals
    // for(int i = 0; i < 12; i++) {
    //     std::cout << "-----------------" << std::endl;
    //     std::cout << i << std::endl;
    //     std::cout << "x: " << vertices_[i].position.x << std::endl;
    //     std::cout << "y: " << vertices_[i].position.y << std::endl;
    //     std::cout << "z: " << vertices_[i].position.z << std::endl;
    // }
    GenerateTerrainQuadrants();


    stbi_image_free(data);

    // Generate indices
    for(int i = 0; i < height-1; i++) {
        for(int j = 0; j < width; j++) {
            for(int k = 0; k < 2; k++) {
                indices_.push_back(j + width * (i + k));
            }
        }
    }

    geometry_ = new BufferGeometry(vertices_, indices_);
}

void Terrain::GenerateTerrainQuadrants() {
    int column = 1;
    int row = width_;
    for(int i = 1; i < depth_ - 1; i++) {
        for(int j = width_; j < width_*depth_; j += width_) {
            TerrainQuadrant quad;
            quad.center_vert = vertices_[j + i].position;
            quad.top = vertices_[j + i - 1].position;
            quad.left = vertices_[j + i - width_].position;
            quad.bottom = vertices_[j + i + 1].position;
            quad.right = vertices_[j + i + width_].position;
            WorldPhysics::ComputeNormal(vertices_[i], quad);
        }
    }
}

void Terrain::DrawTerrain() {
    shader_->Use();
    tex_->Bind();
    transforms_.model = glm::mat4(1.0f);
    transforms_.model = glm::translate(transforms_.model, transforms_.position);
    shader_->setMat4("model", transforms_.model);
    shader_->setVector3f("material.ambient", mat_.ambient);
    shader_->setVector3f("material.specular", mat_.specular);
    shader_->setFloat("material.shininess", mat_.shininess);
    geometry_->DrawGeometry(n_strips_, n_vertices_strip_);
    glUseProgram(0);
}