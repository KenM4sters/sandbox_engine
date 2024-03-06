#pragma once
#include "material/material.h"
#include "geometry/buffer_geometry.h"
#include "../utils/includes.h"

class Mesh {
    public:
        Mesh(Material* material, UBufferGeometry* geometry) : material_(material), geometry_(geometry) { Init();}
        ~Mesh() {}
        void Init();
        Material* GetMaterial() { return material_;}
        Material* SetMaterial(Material* material) {material_ = material; return material_;}
        UBufferGeometry* GetGeometry() {return geometry_;}
        UBufferGeometry* SetGeometry(UBufferGeometry* geometry) {geometry_ = geometry; return geometry_;}
        unsigned int VAO_, VBO_;

    private:
        Material* material_;
        UBufferGeometry* geometry_;
        glm::vec3 scale{1.0f, 1.0f, 1.0f};
        glm::vec3 position{.0f, .0f, .0f};
};