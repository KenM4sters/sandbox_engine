#pragma once
#include "mesh.h"

class BoundingBox {
    public:
        BoundingBox(Shader* shader, Transforms* transforms, std::vector<float> vertices)
            : shader_(shader), mesh_transforms_(transforms)
        {
            geometry_ = new BufferGeometry(vertices, SANDBOX_CUBE_VERTICES_COUNT);
        }
        ~BoundingBox() {}
        void Draw() {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader_->Use();
            mesh_transforms_->model = glm::mat4(1.0f);
            mesh_transforms_->model = glm::translate(mesh_transforms_->model, mesh_transforms_->position);
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
        BufferGeometry* geometry_;
};