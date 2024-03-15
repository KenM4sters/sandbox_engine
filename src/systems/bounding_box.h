#pragma once
#include "mesh.h"

class BoundingBox {
    public:
        BoundingBox(Shader* shader, Transforms* transforms, glm::vec3 scale, glm::vec3 translation = {0.0, 0.0, 0.0})
            : shader_(shader), mesh_transforms_(transforms), scale_(scale), translation_(translation)
        {
            geometry_ = new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT);
        }
        ~BoundingBox() {}
        void Draw() {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader_->Use();
            mesh_transforms_->model = glm::mat4(1.0f);
            mesh_transforms_->model = glm::translate(mesh_transforms_->model, mesh_transforms_->position + translation_);
            mesh_transforms_->model = glm::scale(mesh_transforms_->model, mesh_transforms_->scale );
            mesh_transforms_->model = glm::rotate(mesh_transforms_->model, mesh_transforms_->rotation.rotation_angle, mesh_transforms_->rotation.rotation_axis);
            shader_->setMat4("model", mesh_transforms_->model);
            geometry_->DrawGeometry();
            glUseProgram(0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        Shader* shader_;
        Transforms* mesh_transforms_;
    private:
        glm::vec3 scale_;
        glm::vec3 translation_;
        BufferGeometry* geometry_;
};