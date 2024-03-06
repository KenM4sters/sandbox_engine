#include "scene.h"

Scene::Scene(unsigned int w, unsigned int h) : scr_width_(w), scr_height_(h)  {
    shader_res_ = std::make_unique<SShaderResource>();
    std::cout << "Shader res created!" << std::endl;
}

Scene::~Scene() {

}

void Scene::AddMesh(Mesh* mesh, std::string name) {
    mesh_repo_[name] = mesh;
}

void Scene::Init() {

    // Camera
    camera_ = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    // Shader
    auto shader = shader_res_->AddResource("src/shaders/quad.vert", "src/shaders/quad.frag", nullptr, "test");

    // Test
    Material* material = new Material(shader, std::string("test"));
    UBufferGeometry* geo = new UBufferGeometry(SANDBOX_CUBE);
    Mesh* mesh = new Mesh(material, geo);

    // Add to the scene 
    AddMesh(mesh, "test");

    // Use the appropriate shader program for the currently bound vertex array;
    shader->Use();
}

void Scene::Render() {

    // iterate through mesh repository, binding the VAO, 
    // using the appropriate shader program, and calling the appropraite draw call
    for(const auto& itr : mesh_repo_) {
        auto geo = itr.second->GetGeometry();

        glm::mat4 projection = glm::mat4(1.0f); 
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f); 

        float angle = 20.0f;

        projection = glm::perspective(glm::radians(45.0f), (float)scr_width_ / (float)scr_height_, 0.1f, 100.0f);
        view = camera_->GetViewMatrix();
        model = glm::translate(model, itr.second->position);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        
        auto mat = itr.second->GetMaterial(); 
        auto shader_mat = mat->GetShaderMaterial();
        shader_mat->setMat4("projection", projection);
        shader_mat->setMat4("view", view);
        shader_mat->setMat4("model", model);

        glBindVertexArray(itr.second->VAO_);
        glDrawArrays(GL_TRIANGLES, 0, geo->vert_count_);
        glBindVertexArray(0);
    }
}
