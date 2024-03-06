#include "material.h"

Shader* Material::SetShaderMaterial(Shader* shader) {
    shader_ = shader;
    
    return shader_;
}