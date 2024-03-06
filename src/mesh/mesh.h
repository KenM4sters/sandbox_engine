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
        Mesh(Material* material, UBufferGeometry* geometry, Camera* camera) : 
            material_(material), geometry_(geometry), camera_(camera) { 
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
        glm::vec3 GetRotation() {return rotation_;}

        // Set from vector
        void SetPosition(glm::vec3 pos) {position_ = pos;}
        void SetScale(glm::vec3 scale) {scale_ = scale;}
        void SetRotation(glm::vec3 rotation) {rotation_ = rotation;}

        // Set from scalar
        void SetPosition(float pos) {position_ = glm::vec3(pos);}
        void SetScale(float scale) {scale_ = glm::vec3(scale);}
        void SetRotation(float rotation) {rotation_ = glm::vec3(rotation);}
        
        unsigned int VAO_, VBO_;

    private:
        glm::vec3 scale_{1.0f, 1.0f, 1.0f};
        glm::vec3 position_{0.0f, 0.0f, -2.0f};
        glm::vec3 rotation_{0.0f, 0.0f, 0.0f};

        Camera* camera_;
        Material* material_;
        UBufferGeometry* geometry_;
        Transform transform_;
};