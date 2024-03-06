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

void Mesh::InitTransforms() {
    
}