#include "lights.h"

void SLights::Init() {
    // Bounding Box - used for collision detection
    Shader* bounding_box_shader = shaders_->GetResource("bounding_box");

    Shader* light_shader = shaders_->GetResource("light_cube");
    Texture2D* light_tex = textures_->GetResource("glowstone");
    BasicMesh* light_mesh = new BasicMesh(new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT), light_shader, light_tex);
    light_mesh->transforms_.position = glm::vec3(2.0f, 2.0f, -1.0f);
    light_mesh->ComputeBoundingBox(bounding_box_shader);
    children_["light_cube"] = light_mesh;
}

SShaderResource* SLights::SetLightData() {
    for(auto k : shaders_->GetAllResources()) {
        auto shader = k.second;
        if(shader->type_ == SANDBOX_OBJECT) {
            objects_shaders_.AddResource(k.first, shader);
            for(auto l : children_ ) {
                std::string light_name = l.first;
                shader->Use();
                shader->setVector3f(light_name + ".position", l.second->transforms_.position);
                shader->setVector3f(light_name + ".ambient", l.second->mat_.ambient );
                shader->setVector3f(light_name + ".diffuse", {0.8f, 0.8f, 0.8f});
                shader->setVector3f(light_name + ".specular", {1.0f, 1.0f, 1.0f});
            }
        }
    }
    return &objects_shaders_;
}

void SLights::Draw() {
    for(auto& l : children_) {
        auto light = l.second;
        light->Draw();
    }
}