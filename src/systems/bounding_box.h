#pragma once
#include "mesh.h"

class BoundingBox {
    public:
        BoundingBox(Shader* shader, Transforms* transforms, const std::vector<float> &vertices, BoundingBoxSizes sizes)
            : shader_(shader), mesh_transforms_(transforms), bounding_box_sizes_(sizes)
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

            // Update bounding_box_sizes with any transformations made to the relative mesh.
            bounding_box_sizes_.width *= mesh_transforms_->scale.x;
            bounding_box_sizes_.width *= mesh_transforms_->scale.x;
            bounding_box_sizes_.width *= mesh_transforms_->scale.x;

            bounding_box_sizes_.height *= mesh_transforms_->scale.y;
            bounding_box_sizes_.height *= mesh_transforms_->scale.y;
            bounding_box_sizes_.height *= mesh_transforms_->scale.y;

            bounding_box_sizes_.depth *= mesh_transforms_->scale.z;
            bounding_box_sizes_.depth *= mesh_transforms_->scale.z;
            bounding_box_sizes_.depth *= mesh_transforms_->scale.z;
            
            shader_->setMat4("model", mesh_transforms_->model);
            geometry_->DrawGeometry();
            glUseProgram(0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        Shader* shader_;
        Transforms* mesh_transforms_;
        BoundingBoxSizes bounding_box_sizes_;
    private:
        BufferGeometry* geometry_;
};