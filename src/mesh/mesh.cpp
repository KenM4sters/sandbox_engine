#include "mesh.h"
#include "../utils/logging.h"

void Mesh::InitGeometry() {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    glBufferData(GL_ARRAY_BUFFER, geometry_->vert_count_ * 12, geometry_->vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, geometry_->stride_, geometry_->offset_);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
    // Logging
    Logger::LogGeometry(geometry_->type_, geometry_->stride_, geometry_->vert_count_, geometry_->offset_);
}

void Mesh::UpdateGeometry() {
    glBindVertexArray(VAO_);
    auto attributes_map = geometry_->GetAttributes();
    for(const auto& attrib : *attributes_map) {
        const auto buffer_data = attrib.second.first->GetData();
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data.first)*sizeof(float), buffer_data.first.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(attrib.second.second, buffer_data.second, GL_FLOAT, GL_FALSE, geometry_->stride_, (void*)0);
        glEnableVertexAttribArray(attrib.second.second);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Mesh::InitTransforms() {
    transform_.projection = glm::perspective(camera_->zoom_, scr_wdith_ / scr_height_, 0.1f, 100.0f);
    transform_.view = camera_->GetViewMatrix();
    transform_.model = glm::translate(transform_.model, position_);
    transform_.model = glm::scale(transform_.model, scale_);
    transform_.model = glm::rotate(transform_.model, rotation_.first, rotation_.second);
}

void Mesh::UpdateTransforms() {
    transform_.view = camera_->GetViewMatrix();

    transform_.model = glm::mat4(1.0f);
    transform_.model = glm::translate(transform_.model, position_);
    transform_.model = glm::scale(transform_.model, scale_);
    transform_.model = glm::rotate(transform_.model, rotation_.first, rotation_.second);

    material_->GetShaderMaterial()->Use();
    material_->GetShaderMaterial()->setMat4("projection", transform_.projection);
    material_->GetShaderMaterial()->setMat4("view", transform_.view);
    material_->GetShaderMaterial()->setMat4("model", transform_.model);
}