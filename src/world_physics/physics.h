#pragma once
#include "../utils/includes.h"
#include "../systems/mesh.h"

class WorldPhysics {
    public:
        static void ApplyGravitationalAcceleration(glm::vec3 &acc_vec) {
            acc_vec.y = 0;
        }
        static void UpdateTransforms(Transforms &transforms, float &delta_time) {
            transforms.model = glm::mat4(1.0f);
            transforms.velocity += transforms.accelration * delta_time;
            transforms.position += transforms.velocity * delta_time * 0.005f;
            transforms.model = glm::translate(transforms.model, transforms.position);
            transforms.model = glm::scale(transforms.model, transforms.scale);
            transforms.model = glm::rotate(transforms.model, transforms.rotation.rotation_angle, transforms.rotation.rotation_axis);
        }

        static void ComputeNormal(glm::vec3& vertex_target, TerrainQuadrant& target_quad) {
        }
    private:
        WorldPhysics() {}
};