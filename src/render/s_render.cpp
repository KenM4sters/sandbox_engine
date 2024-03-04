#include "s_render.h"


// Implementation for rendering

void sandbox_render::SRenderer::init(sandbox_window::SWindow *window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    auto gl_window = glfwCreateWindow(window_->width_, window_->height_, window_->title_.c_str(), nullptr, nullptr);
    window_->SetNativeWindow(gl_window); 

    if(gl_window == nullptr) {
        std::cout << "FAILED to create GLFW window!" << std::endl;
        sandbox_render::SRenderer::Terminate();
    }
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED to initalize GLAD!" << std::endl;
    }

    glViewport(0, 0, window_->width_, window_->height_);
}

void sandbox_render::SRenderer::PreRender() {

}

void sandbox_render::SRenderer::PostRender() {

}

void sandbox_render::SRenderer::Terminate() {
    std::cout << "Terminating Window" << std::endl;
    glfwDestroyWindow(static_cast<GLFWwindow*>(window_->GetNativeWindow()));
    glfwTerminate();
}