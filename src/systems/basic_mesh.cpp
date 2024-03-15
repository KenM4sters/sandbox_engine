#include "basic_mesh.h"

void BasicMesh::Draw() {
    shader_->Use();
    transforms_.model = glm::mat4(1.0f);
    // Order matters here and is dependant on the particular use case - neither is right nor wrong,
    // but in our case we want to rotate around their new positions, as opposed to their starting ones.
    transforms_.model = glm::translate(transforms_.model, transforms_.position);
    transforms_.model = glm::scale(transforms_.model, transforms_.scale);
    transforms_.model = glm::rotate(transforms_.model, transforms_.rotation.rotation_angle, transforms_.rotation.rotation_axis);
    shader_->setMat4("model", transforms_.model);
    shader_->setVector3f("material.ambient", mat_.ambient);
    shader_->setVector3f("material.specular", mat_.specular);
    shader_->setFloat("material.shininess", mat_.shininess); 
    for(int i = 0; i < mat_.textures.size(); i++) {
        mat_.textures[i]->Bind(i);
        shader_->setInteger(std::string("material.") + mat_.textures[i]->tex_type_, i);
    }
    geometry_->DrawGeometry();
    glActiveTexture(GL_TEXTURE0);
    bounding_box->Draw();
}

void BasicMesh::ComputeBoundingBox(Shader *shader, float vertices_data) {
    // Regular cube, so we can just use the global cube_vertices variable which holds 
    // the position, normal and tex coords for a cube.
    BoundingBoxSizes sizes = BoundingBoxSizes{1.0f, 1.0f, 1.0f};
    bounding_box = new BoundingBox(shader, &transforms_, cube_vertices, sizes);
}