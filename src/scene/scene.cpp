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
    auto cube_shader= shader_res_->AddResource("src/shaders/cube_1.vert", "src/shaders/cube_1.frag", nullptr, "cube1");
    auto light_cube_shader = shader_res_->AddResource("src/shaders/light_cube.vert", "src/shaders/light_cube.frag", nullptr, "cube2");
    auto floor_shader = shader_res_->AddResource("src/shaders/floor.vert", "src/shaders/floor.frag", nullptr, "floor");

    // Cubes
    Material* cube_mat = new Material(cube_shader, std::string("cube1"));
    UBufferGeometry* cube_geo = new UBufferGeometry(SANDBOX_CUBE);
    cube_geo->AddBufferAttribute("normals", 1, new BufferAtrribute(std::vector<float>(SANDBOX_CUBE_NORMALS), 3));
    Mesh* mesh = new Mesh(cube_mat, cube_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    cube_mat->SetColor(glm::vec3(0.3f, 0.9f, 1.0f));
    AddMesh(mesh, "cube1");
    mesh->SetPosition(glm::vec3(5.0f, 0.0f, -10.0f));
    mesh->UpdateGeometry();

    // Light Cube
    Material* light_cube_mat = new Material(light_cube_shader, std::string("cube2"));
    UBufferGeometry* light_cube_geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh_2 = new Mesh(light_cube_mat, light_cube_geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    light_cube_mat->SetColor(glm::vec3(0.9f, 0.1f, 0.0f));
    AddMesh(mesh_2, "cube2");
    mesh_2->SetPosition(glm::vec3(0.0f, 5.0f, -5.0f));

    // Floor
    Material* floor_mat = new Material(floor_shader, std::string("floor"));
    UBufferGeometry* floor_geo = new UBufferGeometry(SANDBOX_SQUARE);
    floor_mat->SetColor(glm::vec3(0.5f, 0.5f, 0.5f));
    floor_geo->AddBufferAttribute("test2", 1, new BufferAtrribute({1.0f, 1.0f, 1.0f}, 3));    
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
