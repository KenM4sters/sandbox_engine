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
                window_state_ == PLAY ? window_state_ = PAUSE : window_state_ = PLAY;
                if(window_state_ == PLAY) {
                    camera_->bMouseMovementEnabled_ = true;
                    // Locks mouse to the window screen and hides it - GLFW handles recentering the mouse, giving our
                    // camera 6 degrees of freedom with no threshold. 
                    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
                else {
                    camera_->bMouseMovementEnabled_ = false;
                    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
                break;
        }
    }
}
void SWindow::HandleWindowResize(int w, int h) {
    glViewport(0, 0, w, h);
    renderer_->post_processing_->Resize(w, h);
}

SWindow::SWindow() 
    : bIsRunning_(true), window_(nullptr) {
    renderer_ = std::make_unique<SContext>(true);
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
    renderer_->Render(delta_time_);
}