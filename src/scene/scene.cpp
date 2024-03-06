#include "scene.h"

Scene::Scene() {
    shader_res_ = std::make_unique<SShaderResource>();
    std::cout << "Shader res created!" << std::endl;
}

Scene::~Scene() {

}

void Scene::AddMesh(Mesh* mesh, std::string& name) {
    mesh_repo_[name] = mesh;
}

void Scene::Init() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top 
    };

    std::cout << "vertices created! \n";

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Shader
    auto shader = shader_res_->AddResource("src/shaders/quad.vert", "src/shaders/quad.frag", nullptr, "test");
    shader.Use();

    Material* material = new Material(&shader, std::string("test"));
}

void Scene::Render() {
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
