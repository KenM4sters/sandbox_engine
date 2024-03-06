#include "scene.h"

Scene::Scene(unsigned int w, unsigned int h, Camera* camera) : scr_width_(w), scr_height_(h), camera_(camera)  {
    shader_res_ = std::make_unique<SShaderResource>();
    std::cout << "Shader res created!" << std::endl;
}

Scene::~Scene() {}

void Scene::AddMesh(Mesh* mesh, std::string name) {
    mesh_repo_[name] = mesh;
}

void Scene::Init() {
    // Shader
    auto shader = shader_res_->AddResource("src/shaders/quad.vert", "src/shaders/quad.frag", nullptr, "test");
    // Cube
    Material* material = new Material(shader, std::string("test"));
    UBufferGeometry* geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh = new Mesh(material, geo, std::tuple<Camera*, float, float>(camera_, scr_width_, scr_height_));
    // Add to the scene 
    AddMesh(mesh, "test");
    // Use the appropriate shader program for the currently bound vertex array;
    shader->Use();
    // Set initial transformations
    mesh->SetPosition(glm::vec3(0.0f, 0.0f, -40.0f));
}

void Scene::Render(float &delta_time) {
    // iterate through mesh repository, binding the VAO, 
    // using the appropriate shader program, and calling the appropraite draw call
    for(const auto& mesh : mesh_repo_) {
        auto geo = mesh.second->GetGeometry();
        
        mesh.second->SetRotation((float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        mesh.second->UpdateTransforms();

        glBindVertexArray(mesh.second->VAO_);
        glDrawArrays(GL_TRIANGLES, 0, geo->vert_count_);
        glBindVertexArray(0);
    }
}
