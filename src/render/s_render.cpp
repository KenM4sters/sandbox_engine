#include "s_render.h"

// Implementation for rendering

static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto p_window = static_cast<sandbox_window::UWindow*>(glfwGetWindowUserPointer(window));
    p_window->HandleKeyInput(key, scancode, action, mods);
}

static void on_window_resize_callback(GLFWwindow* window, int width, int height) {
    auto p_window = static_cast<sandbox_window::UWindow*>(glfwGetWindowUserPointer(window));
    p_window->HandleWindowResize(width, height);
}

void sandbox_render::SRenderer::init(sandbox_window::UWindow *window) {
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
    glfwSetWindowUserPointer(gl_window, window);
    glfwSetKeyCallback(gl_window, on_key_callback);
    glfwSetFramebufferSizeCallback(gl_window, on_window_resize_callback);
    glfwMakeContextCurrent(gl_window);
}

void sandbox_render::SRenderer::PreRender() {
    std::cout << "PRERENDER" << std::endl;
}

void sandbox_render::SRenderer::PostRender() {

}

void sandbox_render::SRenderer::Terminate() {
    std::cout << "Terminating Window" << std::endl;
    glfwDestroyWindow(static_cast<GLFWwindow*>(window_->GetNativeWindow()));
    glfwTerminate();
}