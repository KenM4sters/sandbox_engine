#pragma once
#include "../../resources/shader.h"
#include "../../resources/s_shader_resource.h"
#include "../../utils/includes.h"

class Material {
    public:
        Material(Shader* shader, std::string name) : shader_(shader), name_(name) {
            shader_->Use();
            shader_->setVector3f("uColor", color_);
        }
        Shader* SetShaderMaterial(Shader* shader); // takes in a name and searches the resource shader for that key
        Shader* GetShaderMaterial() { return shader_; }
        void SetColor(glm::vec3 color) { 
            color_ = color; 
            shader_->Use();
            shader_->setVector3f("uColor", color_);
        }
    private:
        Shader* shader_;
        std::string name_;
        glm::vec3 color_{0.5f, 0.1f, 0.9f};

};