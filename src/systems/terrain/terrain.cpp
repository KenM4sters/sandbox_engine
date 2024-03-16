#include "terrain.h"

void Terrain::InitTerrainMeshData(unsigned char* data, int &width, int &height, int &nr_channels) {
    // These two variables will be used later to generate indices for our terrain mesh data.
    n_strips_ = height - 1;
    n_vertices_strip_ = width * 2;

    // Vertices
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {

            unsigned char* texel = data + (j + width * i) * nr_channels;
            unsigned char y_displacement = texel[0];
            Vertex v;
            v.position.x = -(height/2.0f) + i;
            v.position.y = (int)y_displacement * y_scale_ / 255;
            v.position.z = -(width/2.0f) + j;

            // v.normal.x = 0.0f;
            // v.normal.y = 0.0f;
            // v.normal.z = 0.0f;

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

    // Calculating the normal coordinates for each vertex
    for(int i = 0; i < vertices_.size(); i+=3) {
        glm::vec3 n = glm::cross(
            vertices_[i].position - vertices_[i + 2].position,
            vertices_[i].position - vertices_[i + 1].position
            );
        vertices_[i].normal = n;
        vertices_[i + 1].normal = n;
        vertices_[i + 2].normal = n;
    }

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