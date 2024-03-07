#include "scene.h"

Scene::Scene(unsigned int w, unsigned int h, Camera* camera) : scr_width_(w), scr_height_(h), camera_(camera)  {
    shader_res_ = std::make_unique<SShaderResource>();
    std::cout << "Shader res created!" << std::endl;
}

// Destructor traverses the scene and deletes all geometries, materials and meshes
Scene::~Scene() {
    for(const auto& itr : mesh_repo_) {
        delete itr.second->GetMaterial();
        delete itr.second->GetGeometry();
        delete itr.second;
    }
}

void Scene::AddMesh(Mesh* mesh, std::string name) {
    mesh_repo_[name] = mesh;
}

void Scene::Init() {
    auto cube_1_shader= shader_res_->AddResource("src/shaders/cube_1.vert", "src/shaders/cube_1.frag", nullptr, "cube1");
    auto cube_2_shader = shader_res_->AddResource("src/shaders/cube_2.vert", "src/shaders/cube_2.frag", nullptr, "cube2");
    auto floor_shader = shader_res_->AddResource("src/shaders/floor.vert", "src/shaders/floor.frag", nullptr, "floor");

    // Cube 1
    Material* cube_1_mat = new Material(cube_1_shader, std::string("cube1"));
    cube_1_mat->SetColor(glm::vec3(0.3f, 0.9f, 1.0f));
    UBufferGeometry* cube_1_geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh = new Mesh(cube_1_mat, cube_1_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    AddMesh(mesh, "cube1");
    mesh->SetPosition(glm::vec3(5.0f, 0.0f, -10.0f));

    // Cube 2
    Material* cube_2_mat = new Material(cube_2_shader, std::string("cube2"));
    cube_2_mat->SetColor(glm::vec3(0.9f, 0.1f, 0.0f));
    UBufferGeometry* cube_2_geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh_2 = new Mesh(cube_2_mat, cube_2_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    AddMesh(mesh_2, "cube2");
    mesh_2->SetPosition(glm::vec3(-5.0f, 0.0f, -10.0f));

    // Floor
    Material* floor_mat = new Material(floor_shader, std::string("floor"));
    floor_mat->SetColor(glm::vec3(0.5f, 0.5f, 0.5f));
    UBufferGeometry* floor_geo = new UBufferGeometry(SANDBOX_SQUARE);
    Mesh* floor_mesh = new Mesh(floor_mat, floor_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    AddMesh(floor_mesh, "floor");
    floor_mesh->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    floor_mesh->SetScale(50.0f);
    floor_mesh->SetRotation(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    floor_mesh->UpdateGeometry();

}

void Scene::Render(float &delta_time) {
    // iterate through mesh repository, binding the VAO, 
    // using the appropriate shader program, and calling the appropraite draw call
    for(const auto& mesh : mesh_repo_) {
        auto geo = mesh.second->GetGeometry();
        mesh.second->GetMaterial()->GetShaderMaterial()->Use();
        mesh.second->UpdateTransforms();

        glBindVertexArray(mesh.second->VAO_);
        glDrawArrays(GL_TRIANGLES, 0, geo->vert_count_);
        glBindVertexArray(0);
    }
}
