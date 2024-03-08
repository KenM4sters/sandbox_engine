#include "s_window.h"

// Implementation for window

void SWindow::HandleKeyInput(int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ESCAPE:
                std::cout << "TERMINATING window \n" << std::endl; 
                bIsRunning_ = false;
                break;
            case GLFW_KEY_W:
                std::cout << "KEY PRESSED : W \n";
                break;
            case GLFW_KEY_A:
                std::cout << "KEY PRESSED : A \n";
                break;
            case GLFW_KEY_S:
                std::cout << "KEY PRESSED : S \n";
                break;
            case GLFW_KEY_D:
                std::cout << "KEY PRESSED : D \n";
                break;
            case GLFW_KEY_SPACE:
                std::cout << "KEY PRESSED : SPACE_BAR \n";
                break;
        }
    }
}
void SWindow::HandleWindowResize(int w, int h) {
    glViewport(0, 0, w, h);
}

SWindow::SWindow(bool bPostProcess) 
    : bPostProcessingEnabled(bPostProcess), bIsRunning_(true), window_(nullptr), post_processing_(nullptr) {
    renderer_ = std::make_unique<SContext>();
    
    if(bPostProcessingEnabled) {
        post_processing_shader_ = new Shader;
        int id = post_processing_shader_->ID_;
        post_processing_shader_->Compile("src/shaders/post_processing.vert", "src/shaders/post_processing.frag", nullptr);
        post_processing_ = std::make_unique<PostProcessing>(width_, height_, post_processing_shader_);
    }
}

void SWindow::init(int w, int h, const std::string& t) {
    height_ = h;
    width_ = w;
    title_ = t;

    prev_mouse_pos_x_ = width_ / 2.0f;
    prev_mouse_pos_y_ = height_ / 2.0f;

    renderer_->Init(this);
}
void SWindow::render() {
    auto current_frame = static_cast<float>(glfwGetTime());
    delta_time_ = current_frame - last_frame;
    last_frame = current_frame;
    renderer_->ProcessInput(window_, delta_time_);
    if(!bPostProcessingEnabled) {
        renderer_->PreRender();
        renderer_->SceneRender(delta_time_);
        renderer_->PostRender();
    } else {
        renderer_->RenderWithPostProcessing(post_processing_shader_, std::move(post_processing_), delta_time_);
    }
}