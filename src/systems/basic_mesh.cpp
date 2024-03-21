#include "basic_mesh.h"
#include "../world_physics/physics.h"

void BasicMesh::Draw(float &delta_time) {
    shader_->Use();
    // Order matters here and is dependant on the particular use case - neither is right nor wrong,
    // but in our case we want to rotate around their new positions, as opposed to their starting ones.
    WorldPhysics::UpdateTransforms(transforms_, delta_time);
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
    if(bounding_box != nullptr)
        bounding_box->Draw();
    glUseProgram(0);
}

void BasicMesh::DrawInstanced(float &delta_time, unsigned int instance_count) {
    shader_->Use();
    WorldPhysics::UpdateTransforms(transforms_, delta_time);
    shader_->setMat4("model", transforms_.model);
    shader_->setVector3f("material.ambient", mat_.ambient);
    shader_->setVector3f("material.specular", mat_.specular);
    shader_->setFloat("material.shininess", mat_.shininess); 
    for(int i = 0; i < mat_.textures.size(); i++) {
        mat_.textures[i]->Bind(i);
        shader_->setInteger(std::string("material.") + mat_.textures[i]->tex_type_, i);
        // std::cout << mat_.textures[i]->tex_type_ << std::endl;
    }
    geometry_->DrawGeometryInstanced(instance_count);
    glActiveTexture(GL_TEXTURE0);
    // if(bounding_box != nullptr)
    //     bounding_box->Draw();
    glUseProgram(0);

}

void BasicMesh::ComputeBoundingBox(Shader *shader, float vertices_data) {
    // Regular cube, so we can just use the global cube_vertices variable which holds 
    // the position, normal and tex coords for a cube.
    BoundingBoxSizes sizes = BoundingBoxSizes{1.0f, 1.0f, 1.0f};
    bounding_box = new BoundingBox(shader, &transforms_, cube_vertices, sizes);
}