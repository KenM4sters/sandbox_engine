#include "mesh.h"

void Mesh::InitMesh() {}

void Mesh::DrawMesh() {
    shader_->Use();
    mat_.texture->Bind();
    transforms_.model = glm::mat4(1.0f);
    // Order matters here and is dependant on the particular use case - neither is right nor wrong,
    // but in our case we want to rotate around their new positions, as opposed to their starting ones.
    transforms_.model = glm::translate(transforms_.model, transforms_.position);
    transforms_.model = glm::scale(transforms_.model, transforms_.scale);
    transforms_.model = glm::rotate(transforms_.model, transforms_.rotation_angle, transforms_.rotation_axis);
    shader_->setMat4("model", transforms_.model);
    shader_->setVector3f("material.ambient", mat_.ambient);
    shader_->setInteger("material.diffuse", 0);
    shader_->setVector3f("material.specular", mat_.specular);
    shader_->setFloat("material.shininess", mat_.shininess); 
    geometry_->DrawGeometry();
    mat_.texture->Unbind();
}