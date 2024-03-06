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

void SWindow::init(int w, int h, const std::string& t) {
    height_ = h;
    width_ = w;
    title_ = t;

    renderer_->init(this);

}
void SWindow::render() {
    renderer_->PreRender();
    renderer_->SceneRender();
    renderer_->PostRender();
}