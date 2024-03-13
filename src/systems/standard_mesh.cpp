#include "standard_mesh.h"

void StandardMesh::Draw() {
    unsigned int diffuse_count = 1;
    unsigned int specular_count = 1;
    unsigned int normal_count = 1;
    unsigned int height_count = 1;

    for(unsigned int i = 0; i < textures_.size(); i++) {
        // This is effectively the same as GL_TEXTUREi, which is important since we need each texture to bind
        // to a different texture index so that they don't override each other.
        glActiveTexture(GL_TEXTURE0 + i);
        std::string tex_index;
        std::string name = textures_[i]->tex_type_;
        if(name == "texture_diffuse") {
            tex_index = std::to_string(diffuse_count++);
        } else if(name == "texture_specular") {
            tex_index = std::to_string(specular_count++);
        } else if(name == "texture_normal") {
            tex_index = std::to_string(normal_count++);
        } else if(name == "texture_height") {
            tex_index = std::to_string(height_count++);
        }
        shader_.Use();
        shader_.setInteger(name + tex_index, textures_[i]->ID_);
        textures_[i]->Bind();
    };

    geometry_->DrawGeometry();
    glActiveTexture(GL_TEXTURE0);
}   