#pragma once
#include "../../resources/shader.h"
#include "../../resources/texture.h"
#include "../../utils/includes.h"

class Material {
    public:
        Material(Shader* shader, std::string name, Texture2D* tex = nullptr) : 
            shader_(shader), name_(name), tex_(tex) 
        {
            shader_->Use();
            shader_->setVector3f("uColor", color_);
        }
        ~Material() {
            #ifdef SANDBOX_DEBUG 
                std::cout << "Material is being destroyed!" << std::endl;
            #endif
        }
        Shader* GetShaderMaterial() { return shader_; }
        Texture2D* GetTexture() { return tex_; }
        std::string GetShaderMaterialName() const { return name_;}
        glm::vec3 GetColor() const { return color_; }
        Shader* SetShaderMaterial(Shader* shader); 
        Texture2D* SetTexture(Texture2D* tex) {tex_ = tex; return tex_;}
        void SetColor(glm::vec3 color) { 
            color_ = color; 
            shader_->Use();
            shader_->setVector3f("uColor", color_);
        }

    private:
        Shader* shader_;
        Texture2D* tex_;
        std::string name_;
        glm::vec3 color_{0.5f, 0.1f, 0.9f};

};