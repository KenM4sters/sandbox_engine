#include "mesh.h"
#include "../utils/logging.h"
#define _DEBUG

void Mesh::InitGeometry() {
    glGenVertexArrays(1, &VAO_);
    UpdateGeometry();
}

void Mesh::UpdateGeometry() {
    // Only a single vertex array is needed and must be bound before binding any additional vertex buffers.
    glBindVertexArray(VAO_);
    auto attributes_map = geometry_->GetAttributes();
    for(const auto& attrib : *attributes_map) {
        const auto buffer_data = attrib.second.first->GetData();
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, buffer_data.first.size() * sizeof(float), buffer_data.first.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(attrib.second.second, buffer_data.second, GL_FLOAT, GL_FALSE, buffer_data.second * sizeof(float), (void*)0);
        glEnableVertexAttribArray(attrib.second.second);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        #ifdef _DEBUG
        Logger::LogAttributes(material_->GetShaderMaterialName(), geometry_->type_, 
            buffer_data.first.size() * sizeof(float), buffer_data.second * sizeof(float), 0);
        #endif
    }

}

void Mesh::InitUniforms() {
    transform_.projection = glm::perspective(camera_->zoom_, scr_wdith_ / scr_height_, 0.1f, 100.0f);
    transform_.view = camera_->GetViewMatrix();
    transform_.model = glm::translate(transform_.model, position_);
    transform_.model = glm::scale(transform_.model, scale_);
    transform_.model = glm::rotate(transform_.model, rotation_.first, rotation_.second);
}

void Mesh::UpdateUniforms(Mesh* light_mesh, glm::vec3& camera_position) {
    transform_.view = camera_->GetViewMatrix();
    // model matrix needs to be reset to the identity matrix on each frame, since we don't want to stack transformations.
    transform_.model = glm::mat4(1.0f);

    // Order matters here and is dependant on the particular use case - neither is right nor wrong,
    // but in our case we want to rotate around their new positions, as opposed to their starting ones.
    transform_.model = glm::translate(transform_.model, position_);
    transform_.model = glm::scale(transform_.model, scale_);
    transform_.model = glm::rotate(transform_.model, rotation_.first, rotation_.second);

    // Make sure the right shader is being used, which is simple in our case since we have a getter
    // method for the shader material. 
    material_->GetShaderMaterial()->Use();
    material_->GetShaderMaterial()->setMat4("projection", transform_.projection);
    material_->GetShaderMaterial()->setMat4("view", transform_.view);
    material_->GetShaderMaterial()->setMat4("model", transform_.model);
    material_->GetShaderMaterial()->setVector3f("camera_pos", camera_position);
    material_->GetShaderMaterial()->setVector3f("light.position", *light_mesh->GetPosition());
    material_->GetShaderMaterial()->setVector3f("light.ambient", light_mesh->material_->GetColor());
    material_->GetShaderMaterial()->setVector3f("light.diffuse", {0.8f, 0.8f, 0.8f});
    material_->GetShaderMaterial()->setVector3f("light.specular", {1.0f, 1.0f, 1.0f});
    material_->GetShaderMaterial()->setVector3f("material.ambient", {0.1f, 0.5f, 0.3f});
    material_->GetShaderMaterial()->setVector3f("material.diffuse", {1.0f, 0.5f, 0.2f});
    material_->GetShaderMaterial()->setVector3f("material.specular", {0.5f, 0.5f, 0.5f});
    material_->GetShaderMaterial()->setFloat("material.shininess", 32.0f); 
}