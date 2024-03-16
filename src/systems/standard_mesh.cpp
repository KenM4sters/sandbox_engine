#include "standard_mesh.h"
#include "../world_physics/physics.h"

void StandardMesh::Draw(float &delta_time) {
    unsigned int diffuse_count = 1;
    unsigned int specular_count = 1;
    unsigned int normal_count = 1;
    unsigned int height_count = 1;

    for(unsigned int i = 0; i < textures_.size(); i++) {
        std::string tex_index;
        std::string name = textures_[i].tex_type_;
        if(name == "texture_diffuse") {
            tex_index = std::to_string(diffuse_count++);
        } else if(name == "texture_specular") {
            tex_index = std::to_string(specular_count++);
        } else if(name == "texture_normal") {
            tex_index = std::to_string(normal_count++);
        } else if(name == "texture_height") {
            tex_index = std::to_string(height_count++);
        }
        shader_->Use();
        textures_[i].Bind(i);
        shader_->setInteger(name + tex_index, i);
    };
    WorldPhysics::UpdateTransforms(transforms_, delta_time);
    shader_->setMat4("model", transforms_.model);
    geometry_.DrawGeometry();
    glActiveTexture(GL_TEXTURE0);
}   
