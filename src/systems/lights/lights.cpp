#include "lights.h"
#include "../../world_physics/physics.h"
#include "../../context/interface.h"

void SLights::Init() {
    // Bounding Box - used for collision detection
    Shader* bounding_box_shader = shaders_->GetResource("bounding_box");

    Shader* light_shader = shaders_->GetResource("light_cube");
    Texture2D* light_tex = textures_->GetResource("glowstone");
    BasicMesh* light_mesh = new BasicMesh(new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT), light_shader, light_tex);
    light_mesh->transforms_.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    light_mesh->transforms_.position = glm::vec3(500, 300, -500);
    light_mesh->mat_.ambient = glm::vec3(0.4f);
    // light_mesh->ComputeBoundingBox(bounding_box_shader);
    children_["light_cube"] = light_mesh;

    Model* sun = new Model("assets/models/sphere.obj", light_shader, bounding_box_shader);
    sun->transforms_->position = glm::vec3(500, 100, -500);
    models_["sun"] = sun;
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

void SLights::UpdateLights() {
    for(auto &obj : objects_shaders_.GetAllResources()) {
        for(auto &l : children_) {
            std::string light_name = l.first;
            obj.second->Use();
            obj.second->setVector3f(light_name + ".position", l.second->transforms_.position);
            obj.second->setVector3f(light_name + ".ambient", l.second->mat_.ambient );
            obj.second->setVector3f(light_name + ".diffuse", {0.5f, 0.5f, 0.5f});
            obj.second->setVector3f(light_name + ".specular", {1.0f, 1.0f, 1.0f});
        }
    }
}

void SLights::Draw(float &delta_time) {
    for(auto& l : children_) {
        auto light = l.second;
        WorldPhysics::ApplyGravitationalAcceleration(light->transforms_.accelration);
        light->Draw(delta_time);
    }
    for(auto& m : models_) {
        auto model = m.second;
        WorldPhysics::ApplyGravitationalAcceleration(model->transforms_->accelration);
        model->DrawModel(delta_time);
        std::string name_x = m.first + " scaleX: ";
        std::string name_y = m.first + " scaleY: ";
        std::string name_z = m.first + " scaleZ: ";
        ImGui::InputFloat(name_x.c_str(), &m.second->transforms_->scale.x, 0.1f, 100.0f);    
        ImGui::InputFloat(name_y.c_str(), &m.second->transforms_->scale.y, 0.1f, 100.0f);    
        ImGui::InputFloat(name_z.c_str(), &m.second->transforms_->scale.z, 0.1f, 100.0f);    
    }
}