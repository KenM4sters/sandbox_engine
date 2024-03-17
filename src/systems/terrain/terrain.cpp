#include "terrain.h"
#include "../../world_physics/physics.h"

void Terrain::InitTerrainMeshData(unsigned char* data, int &width, int &height, int &nr_channels) {
    // These two variables will be used later to generate indices for our terrain mesh data.
    n_strips_ = height - 1;
    n_vertices_strip_ = width * 2;


    // Vertices
    int count = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            unsigned char* texel = data + (j + width * i) * nr_channels;
            unsigned char y_displacement = texel[0];
            Vertex v;
            v.position.x = -(height/2.0f) + i;
            v.position.y = (int)y_displacement * y_scale_ / 255;
            v.position.z = -(width/2.0f) + j;

            v.tex_coords.x = i % 2 == 0 ? 0.0f : 1.0f;
            v.tex_coords.y = j % 2 == 0 ? 0.0f : 1.0f;

            v.tangent.x = 0.0f;
            v.tangent.y = 0.0f;
            v.tangent.z = 0.0f;

            v.bi_tangent.x = 0.0f;
            v.bi_tangent.y = 0.0f;
            v.bi_tangent.z = 0.0f;

            v.texel_val = y_displacement / 255;

            vertices_.push_back(v);
        }
    }

    // Generates normals from terrain quadrants, where each quadrant contains a center vertex and
    // the 4 adjacent veritces (up, down, left, right), used to create an average normal for blended
    // shading.
    GenerateTerrainNormals();
    GenerateTerrainQuadrants(4);
    stbi_image_free(data);

    // Generate indices
    for(int i = 0; i < height-1; i++) {
        for(int j = 0; j < width; j++) {
            for(int k = 0; k < 2; k++) {
                indices_.push_back(j + width * (i + k));
            }
        }
    }  

    // Create geometry from vertices and indices.
    // Buffer Geometry class has a special constructor designed for this terrain class. 
    geometry_ = new BufferGeometry(vertices_, indices_);
}

void Terrain::GenerateTerrainNormals() {
    int counter = 1;
    for(int i = 1; i < depth_ - 2; i++) {
        for(int j = width_; j < (width_*depth_) - width_; j += width_) {
            VertexQuadrant quad;
            quad.center_vert = vertices_[j + i].position;
            quad.top = vertices_[j + i - 1].position; 
            quad.left = vertices_[j + i - width_].position;
            quad.bottom = vertices_[j + i + 1].position;
            quad.right = vertices_[j + i + width_].position;
            WorldPhysics::ComputeNormal(vertices_[j + i], quad);
            // terrain_quadrants_["AREA_" + std::to_string(counter)] = quad;
            counter++;
        }
    }
}
void Terrain::GenerateTerrainQuadrants(unsigned int base_num) {
    if (base_num < 2) 
        throw std::runtime_error("Terrain::GenerateTerrainQuadrants() - invalid base value - value must be at least 2");
    int num_quads = pow(base_num, 2);
    int quad_size = width_ / num_quads;
}

void Terrain::GenerateScenary(Shader* shader, Material& scenery_mat) {
    std::vector<Vertex> flat_vertices;
    for(const auto& v : vertices_) {
        // if(glm::dot(
        //     v.normal, 
        //     glm::vec3(0.0f, 1.0f, 0.0f)) / glm::acos(glm::length(v.normal)/glm::length(glm::vec3(0.0f, 1.0f, 0.0f))) < 0.3) {
        //     flat_vertices.push_back(v);
        // }
        if(v.position.y < 20) flat_vertices.push_back(v);
    }
    scenery = new Scenery(shader, scenery_mat, flat_vertices);
}

void Terrain::DrawTerrain(float& delta_time) {
    shader_->Use();
    transforms_.model = glm::mat4(1.0f);
    shader_->setMat4("model", transforms_.model);
    shader_->setVector3f("material.ambient", mat_.ambient);
    shader_->setVector3f("material.specular", mat_.specular);
    shader_->setFloat("material.shininess", mat_.shininess); 
    for(int i = 0; i < mat_.textures.size(); i++) {
        mat_.textures[i]->Bind(i);
        shader_->setInteger(std::string("material.") + mat_.textures[i]->tex_type_, i);
    }
    geometry_->DrawGeometry(n_strips_, n_vertices_strip_);
    glActiveTexture(GL_TEXTURE0);
    glUseProgram(0);
    // Draw the scenery after the terrain, and make sure textures and shaders have been unbounded 
    // out of courtesy.
    scenery->Draw(delta_time);
}