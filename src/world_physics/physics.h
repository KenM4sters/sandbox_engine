#pragma once
#include "../utils/includes.h"
#include "../systems/mesh.h"
#include "../systems/terrain/terrain.h"

class WorldPhysics {
    public:
        static void ApplyGravitationalAcceleration(glm::vec3 &acc_vec) {
            acc_vec.y = 0.0;
        }
        static void UpdateTransforms(Transforms &transforms, float &delta_time) {
            transforms.model = glm::mat4(1.0f);
            transforms.velocity += transforms.accelration * delta_time;
            transforms.position += transforms.velocity * delta_time * 0.005f;
            transforms.model = glm::translate(transforms.model, transforms.position);
            transforms.model = glm::scale(transforms.model, transforms.scale);
            transforms.model = glm::rotate(transforms.model, transforms.rotation.rotation_angle, transforms.rotation.rotation_axis);
        }

        static void ComputeNormal(Vertex& v, TerrainQuadrant& q) {
            static int counter = 0;
            glm::vec3 tr = glm::normalize(glm::cross(
                q.right - v.position,
                q.top - v.position
            ));
            glm::vec3 br = glm::normalize(glm::cross(
                q.bottom - v.position,
                q.right - v.position
            ));
            glm::vec3 bl = glm::normalize(glm::cross(
                q.left - v.position,
                q.bottom - v.position
            ));
            glm::vec3 tl = glm::normalize(glm::cross(
                q.top - v.position,
                q.left - v.position
            ));

            v.normal = glm::normalize(tr + br + bl + tl);
            if(counter < 50) {
                std::cout << v.position.x << std::endl; 
                std::cout << v.position.y << std::endl; 
                std::cout << v.position.z << std::endl; 
            }
            counter++;
        }
    private:
        WorldPhysics() {}
};