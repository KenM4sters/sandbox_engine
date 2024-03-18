#include "objects.h"
#include "../../world_physics/physics.h"
void SObjects::Init() {

    // Bounding Box - used for collision detection
    Shader* bounding_box_shader = shaders_->GetResource("bounding_box");

    // Mario Cube
    Shader* cube_shader = shaders_->GetResource("cube");
    Texture2D* mario_tex = textures_->GetResource("mario");
    Texture2D* test_tex = textures_->GetResource("sonic");
    std::vector<Texture2D*> tex_vec = {mario_tex,test_tex };
    BasicMesh* cube_mesh = new BasicMesh(new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT), cube_shader, tex_vec);
    cube_mesh->transforms_.position = glm::vec3(2.0f, 14.6f, 0.0f);
    // cube_mesh->ComputeBoundingBox(bounding_box_shader);
    children_["cube"] = cube_mesh;

    // Models 
    Shader* model_shader = shaders_->GetResource("model");


    // p1
    Model* m_p1 = new Model("assets/models/2021 McLaren Artura/2021 McLaren Artura.obj", model_shader, bounding_box_shader);
    m_p1->transforms_->position = glm::vec3(8.0f, 13.5f, -1.0f);
    m_p1->transforms_->rotation = {glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
    m_p1->transforms_->scale = glm::vec3(0.2f, 0.2f, 0.2f);
    models_["m_p1"] = m_p1;
    // m_p1->ComputeBoundingBox();


    // backpack
    Model* back_pack = new Model("assets/models/backpack/backpack.obj", model_shader, bounding_box_shader);
    back_pack->transforms_->position = glm::vec3(-2.0f, 14.5f, -4.0f);
    back_pack->transforms_->scale = glm::vec3(0.2f, 0.2f, 0.2f);
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
    }
}