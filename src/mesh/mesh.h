#pragma once
#include "material/material.h"
#include "geometry/buffer_geometry.h"
#include "../utils/includes.h"
#include "../camera/camera.h"

struct Transform {
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
};

class Mesh {
    public:
        Mesh(Material* material, UBufferGeometry* geometry, std::tuple<Camera*, float, float> camera_data) : 
            material_(material), geometry_(geometry), camera_(std::get<0>(camera_data)), 
            scr_wdith_(std::get<1>(camera_data)), scr_height_(std::get<2>(camera_data)) 
            { 
                InitGeometry();
                InitTransforms();
            }
            
        ~Mesh() {}
        void InitGeometry();
        void InitTransforms();
        Material* GetMaterial() {return material_;}
        Material* SetMaterial(Material* material) {material_ = material; return material_;}
        UBufferGeometry* GetGeometry() {return geometry_;}
        UBufferGeometry* SetGeometry(UBufferGeometry* geometry) {geometry_ = geometry; return geometry_;}

        glm::vec3 GetPosition() {return position_;}
        glm::vec3 GetScale() {return scale_;}
        std::pair<float, glm::vec3> GetRotation() {return rotation_;}

        // Set from vector
        void SetPosition(glm::vec3 pos) {position_ = pos;}
        void SetScale(glm::vec3 scale) {scale_ = scale;}
        // Assumes rotation around the y-axis if left undefined
        void SetRotation(float angle, glm::vec3 axis = glm::vec3(0.0, 1.0f, 0.0f)) 
        {
            rotation_.first = angle; 
            rotation_.second = axis;
        }

        // Set from scalar
        void SetPosition(float pos) {position_ = glm::vec3(pos);}
        void SetScale(float scale) {scale_ = glm::vec3(scale);}

        void UpdateTransforms();
        
        unsigned int VAO_, VBO_;

    private:
        glm::vec3 scale_{1.0f, 1.0f, 1.0f};
        glm::vec3 position_{0.0f, 0.0f, -2.0f};
        std::pair<float, glm::vec3> rotation_;

        Camera* camera_;
        Material* material_;
        UBufferGeometry* geometry_;
        Transform transform_;

        float scr_wdith_, scr_height_;
};