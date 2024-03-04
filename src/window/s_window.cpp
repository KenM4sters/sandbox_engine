#include "s_window.h"

// Implementation for window

void sandbox_window::SWindow::HandleKeyInput(int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) std::cout << "Key Pressed!" << std::endl;
}
void sandbox_window::SWindow::HandleWindowResize(int w, int h) {}

void sandbox_window::SWindow::init(int w, int h, const std::string& t) {

    height_ = h;
    width_ = w;
    title_ = t;

    renderer_->init(this);

}
void sandbox_window::SWindow::render() {
    renderer_->PreRender();
    renderer_->PostRender();
}