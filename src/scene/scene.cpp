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
    auto shader = shader_res_->AddResource("src/shaders/cube_1.vert", "src/shaders/cube_1.frag", nullptr, "cube1");
    auto shader_2 = shader_res_->AddResource("src/shaders/cube_2.vert", "src/shaders/cube_2.frag", nullptr, "cube2");

    // Cube 1
    Material* material = new Material(shader, std::string("cube1"));
    material->SetColor(glm::vec3(0.3f, 0.9f, 1.0f));
    UBufferGeometry* geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh = new Mesh(material, geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    AddMesh(mesh, "cube1");
    mesh->SetPosition(glm::vec3(5.0f, 0.0f, -10.0f));

    // Cube 2
    Material* mat_2 = new Material(shader_2, std::string("cube2"));
    mat_2->SetColor(glm::vec3(0.9f, 0.1f, 0.0f));
    UBufferGeometry* geo_2 = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh_2 = new Mesh(mat_2, geo_2, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    AddMesh(mesh_2, "cube2");
    mesh_2->SetPosition(glm::vec3(-5.0f, 0.0f, -10.0f));
}

void Scene::Render(float &delta_time) {
    // iterate through mesh repository, binding the VAO, 
    // using the appropriate shader program, and calling the appropraite draw call
    for(const auto& mesh : mesh_repo_) {
        auto geo = mesh.second->GetGeometry();
        mesh.second->GetMaterial()->GetShaderMaterial()->Use();

        mesh.second->SetRotation((float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        mesh.second->UpdateTransforms();

        glBindVertexArray(mesh.second->VAO_);
        glDrawArrays(GL_TRIANGLES, 0, geo->vert_count_);
        glBindVertexArray(0);
    }
}
