#pragma once
#include "mesh.h"

class BoundingBox {
    public:
        BoundingBox(Shader* shader, Transforms* transforms, unsigned int width, unsigned int height, unsigned int depth)
            : shader_(shader), transforms_(transforms), width_(width), height_(height), depth_(depth) 
        {
            geometry_ = new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT);
        }
        ~BoundingBox() {}
        void Draw() {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader_->Use();
            transforms_->model = glm::mat4(1.0f);
            transforms_->model = glm::translate(transforms_->model, transforms_->position);
            transforms_->model = glm::scale(transforms_->model, transforms_->scale);
            transforms_->model = glm::scale(transforms_->model, glm::vec3(2.0f, 2.0f, 2.0f));
            transforms_->model = glm::rotate(transforms_->model, transforms_->rotation.rotation_angle, transforms_->rotation.rotation_axis);
            shader_->setMat4("model", transforms_->model);
            geometry_->DrawGeometry();
            glUseProgram(0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        Shader* shader_;
        Transforms* transforms_;
    private:
        unsigned int height_;
        unsigned int width_;
        unsigned int depth_;
        BufferGeometry* geometry_;
};