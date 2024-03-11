#include "skybox.h"


Skybox::Skybox(std::vector<float> vertices, std::vector<std::string> face_textures, Shader* shader, Camera* camera) {
    tex_ = new Tex();
    shader_ = shader;
    camera_ = camera;
    face_textures_ = face_textures;
    vertices_ = vertices;

    LoadCubeMap();
    InitCube();
}

unsigned int* Skybox::LoadCubeMap() const {
    glGenTextures(1, &tex_->ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex_->ID);
    int w, h, nr_channels;
    stbi_set_flip_vertically_on_load(false);
    for(int i = 0; i < face_textures_.size(); i++) {
        unsigned char* data = stbi_load(face_textures_[i].c_str(), &w, &h, &nr_channels, 0);
        if(data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "ERROR::Cubemap texture failed to load at path: " << face_textures_[i] << std::endl;
            stbi_image_free(data);
        } 
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return &tex_->ID;
}

void Skybox::InitCube() {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(0));
    glEnableVertexAttribArray(0);
    transforms_.projection = glm::perspective(camera_->zoom_, 800.0f / 600.0f, 0.1f, 100.0f);
}

void Skybox::DrawCube() {
    // We don't want the translation part of the matrix since it shouldn't move when the camera
    // moves, so we get rid of the translation part of the matrix by reducing it to a mat3
    // and then refilling it to a mat4 with zero translation component.
    transforms_.view = glm::mat4(glm::mat3(camera_->GetViewMatrix()));
    shader_->Use();
    shader_->setMat4("view", transforms_.view);
    shader_->setMat4("projection", transforms_.projection);
    glBindVertexArray(VAO_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex_->ID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}