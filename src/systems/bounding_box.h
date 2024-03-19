#pragma once
#include "mesh.h"
#include "system_includes.h"

/**
 * The BoundingBox class is repsonsible for storing vertex data for a cube of known size and rendering
 * that cube to the scene. Bounding boxes are used to simplify collision detection as they each wrap around
 * a chose object in the scene and are used by the collision handler instead of the objects themselves.
*/

class BoundingBox {
    public:
        // Constructor instantiates a new BufferGeometry instance with vertex data that defines the size of the box
        // Bounding boxes have their size directly determined in the vertex data instead of being scaled to wrap 
        // around objects.
        BoundingBox(Shader* shader, 
        Transforms* transforms, const std::vector<float> &vertices, BoundingBoxSizes sizes)
            : shader_(shader), mesh_transforms_(transforms), bounding_box_sizes_(sizes)
        {
            geometry_ = new BufferGeometry(vertices, SANDBOX_CUBE_VERTICES_COUNT);
        }
        ~BoundingBox() {
            delete geometry_;
        }
        // Sets bounding box transform uniforms and calls geometry_::DrawGeometry() to render the objects to the scene.
        void Draw() {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe - optional.
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
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Diable wireframe since we don't want our objects to render in wireframe.
        }
        Shader* shader_;
        Transforms* mesh_transforms_;
        BoundingBoxSizes bounding_box_sizes_;
    private:
        BufferGeometry* geometry_;
};