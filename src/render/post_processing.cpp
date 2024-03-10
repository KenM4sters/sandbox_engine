#include "post_processing.h"

PostProcessing::PostProcessing(unsigned int width, unsigned int height, SShaderResource* fbo_shader_res) :
    width_(width), height_(height) {
        shader_ = fbo_shader_res->AddResource("src/shaders/post_processing.vert", "src/shaders/post_processing.frag", nullptr, "fbo_quad");
        shader_->Use();
        glGenFramebuffers(1, &FBO_);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
        glGenTextures(1, &tex_.ID_);
        glBindTexture(GL_TEXTURE_2D, tex_.ID_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2 * width_, 2 * height_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_.ID_, 0);

        glGenRenderbuffers(1, &RBO_);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 2 * width_, 2 * height_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO_);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::Failed to create frame buffer!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        InitQuad();
}

void PostProcessing::InitQuad() {
    unsigned int VBO;
    float vertices[] = {
        // pos        // tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PostProcessing::BeginRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO_);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessing::RenderQuad() {
    shader_->Use();
    glBindVertexArray(VAO_);
    glActiveTexture(tex_.ID_);
    glBindTexture(GL_TEXTURE_2D, tex_.ID_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PostProcessing::EndRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}