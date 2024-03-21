#include "objects.h"
#include "../../world_physics/physics.h"
#include "../../context/interface.h"
void SObjects::Init() {

    // Bounding Box - used for collision detection
    Shader* bounding_box_shader = shaders_->GetResource("bounding_box");
    Shader* sky_sphere_shader = shaders_->GetResource("sky_sphere");
    Shader* model_shader = shaders_->GetResource("model");
    Shader* cube_shader = shaders_->GetResource("cube");

    // Mario Cube
    Texture2D* mario_tex = textures_->GetResource("mario");
    Texture2D* test_tex = textures_->GetResource("sonic");
    std::vector<Texture2D*> tex_vec = {mario_tex,test_tex };
    BasicMesh* cube_mesh = new BasicMesh(new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT), cube_shader, tex_vec);
    cube_mesh->transforms_.position = glm::vec3(2.0f, 14.6f, 0.0f);
    // cube_mesh->ComputeBoundingBox(bounding_box_shader);
    children_["cube"] = cube_mesh;

    // Models 
    // p1
    Model* m_p1 = new Model("assets/models/2021 McLaren Artura/2021 McLaren Artura.obj", model_shader, bounding_box_shader);
    m_p1->transforms_->scale = glm::vec3(.2f, .2f, .2f);
    m_p1->transforms_->rotation = {glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
    m_p1->transforms_->position = glm::vec3(8.0f, 13.5f, -1.0f);
    models_["m_p1"] = m_p1;
    // m_p1->ComputeBoundingBox();

    // backpack
    Model* back_pack = new Model("assets/models/backpack/backpack.obj", model_shader, bounding_box_shader);
    back_pack->transforms_->scale = glm::vec3(0.2f, 0.2f, 0.2f);
    back_pack->transforms_->position = glm::vec3(-2.0f, 14.5f, -4.0f);
    models_["backpack"] = back_pack;
    // back_pack->ComputeBoundingBox();
}

void SObjects::Draw(float &delta_time) {
    for(auto& k : children_) {
        auto mesh = k.second;
        WorldPhysics::ApplyGravitationalAcceleration(mesh->transforms_.accelration);
        mesh->Draw(delta_time);
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