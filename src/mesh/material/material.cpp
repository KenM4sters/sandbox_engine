#include "material.h"

Shader* Material::SetShaderMaterial(std::string shader_name) {
    if(!shader_resource_->res_.count(shader_name))
        throw std::runtime_error("ERROR::Material name must be a valid shader resource key!");
    else
        material_ = shader_resource_->res_.find(shader_name);
    
    return &material_->second;
}