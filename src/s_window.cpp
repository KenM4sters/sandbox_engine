#include "s_window.h"

// Implementation for window

void SWindow::HandleKeyInput(int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        std::cout << "TERMINATING window" << std::endl; 
        bIsRunning_ = false;
    }
}

void SWindow::HandleWindowResize(int w, int h) {

}

void SWindow::init(int w, int h, const std::string& t) {
    height_ = h;
    width_ = w;
    title_ = t;

    renderer_->init(this);

}
void SWindow::render() {
    renderer_->PreRender();
    renderer_->PostRender();
}