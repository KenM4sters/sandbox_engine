#include "scene.h"

Scene::Scene() {
    shader_res_ = std::make_unique<SShaderResource>();
    std::cout << "Shader res created!" << std::endl;
}

Scene::~Scene() {

}

void Scene::AddMesh(Mesh* mesh, std::string name) {
    mesh_repo_[name] = mesh;
}

void Scene::Init() {
    // Shader
    auto shader = shader_res_->AddResource("src/shaders/quad.vert", "src/shaders/quad.frag", nullptr, "test");

    // Test
    Material* material = new Material(&shader, std::string("test"));
    UBufferGeometry* geo = new UBufferGeometry(SANDBOX_TRIANGLE);
    Mesh* mesh = new Mesh(material, geo);

    // Add to the scene 
    AddMesh(mesh, "test");

    // Use the appropriate shader program for the currently bound vertex array;
    shader.Use();
}

void Scene::Render() {

    // iterate through mesh repository, binding the VAO, 
    // using the appropriate shader program, and calling the appropraite draw call
    for(const auto& itr : mesh_repo_) {
        auto geo = itr.second->GetGeometry();
        glBindVertexArray(itr.second->VAO_);
        glDrawArrays(GL_TRIANGLES, 0, geo->vert_count_);
        glBindVertexArray(0);
    }
}
