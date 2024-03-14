#include "objects.h"


void SObjects::Init() {
    const std::vector<float> cube_vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    const std::vector<float> square_vertices = {
        0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
       -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, -1.0f  
    };
    const std::vector<unsigned int> square_indices = {
        0, 1, 3,   
        1, 2, 3 
    };

    // Mario Cube
    Shader* cube_shader = shaders_->GetResource("cube");
    Texture2D* mario_tex = textures_->GetResource("mario");
    Texture2D* test_tex = textures_->GetResource("sonic");
    std::vector<Texture2D*> tex_vec = {mario_tex,test_tex };
    BasicMesh* cube_mesh = new BasicMesh(new BufferGeometry(cube_vertices, SANDBOX_CUBE_VERTICES_COUNT), cube_shader, tex_vec);
    children_["cube"] = cube_mesh;

    // Floor
    // Shader* floor_shader = shaders_->GetResource("floor");
    // Texture2D* sand_tex = textures_->GetResource("sand");
    // BasicMesh* floor_mesh = new BasicMesh(new BufferGeometry(square_vertices, square_indices, SANDBOX_CUBE_VERTICES_COUNT), floor_shader, sand_tex);
    // floor_mesh->transforms_.position = glm::vec3(0.0f, -0.75f, 0.0f);
    // floor_mesh->transforms_.rotation = {glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f),};
    // floor_mesh->transforms_.scale = glm::vec3(1000.0f, 0.0f, 1000.0f);
    // children_["floor"] = floor_mesh;

    // Models 
    Shader* model_shader = shaders_->GetResource("model");
    Model* back_pack = new Model("assets/models/backpack/backpack.obj", model_shader);
    back_pack->transforms_.position = glm::vec3(-2.0f, 0.0f, -4.0f);
    back_pack->transforms_.scale = glm::vec3(0.2f, 0.2f, 0.2f);
    models_["backpack"] = back_pack;

}

void SObjects::Draw() {
    for(auto& k : children_) {
        auto mesh = k.second;
        mesh->DrawMesh();
    }
    for(auto& m : models_) {
        auto model = m.second;
        model->DrawModel();
    }
}