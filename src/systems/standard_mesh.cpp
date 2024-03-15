#include "standard_mesh.h"

void StandardMesh::Draw() {
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
    transforms_.model = glm::mat4(1.0f);
    // Order matters here and is dependant on the particular use case - neither is right nor wrong,
    // but in our case we want to rotate around their new positions, as opposed to their starting ones.
    transforms_.model = glm::translate(transforms_.model, transforms_.position);
    transforms_.model = glm::scale(transforms_.model, transforms_.scale);
    transforms_.model = glm::rotate(transforms_.model, transforms_.rotation.rotation_angle, transforms_.rotation.rotation_axis);
    shader_->setMat4("model", transforms_.model);
    geometry_.DrawGeometry();
    glActiveTexture(GL_TEXTURE0);
}   

void StandardMesh::ComputeBoundingBox(Shader* shader) {

}