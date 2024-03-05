#include "s_context.h"


// Implementation for rendering

static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto p_window = static_cast<UWindow*>(glfwGetWindowUserPointer(window));
    p_window->HandleKeyInput(key, scancode, action, mods);
}

static void on_window_resize_callback(GLFWwindow* window, int width, int height) {
    auto p_window = static_cast<UWindow*>(glfwGetWindowUserPointer(window));
    p_window->HandleWindowResize(width, height);
}

void SContext::init(UWindow *window) {
    window_ = window;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    std::cout<<"INITIALIZING::GLFWWindow"<<std::endl;
    auto gl_window = glfwCreateWindow(window_->width_, window_->height_, window_->title_.c_str(), nullptr, nullptr);
    window_->SetNativeWindow(gl_window); 

    if(gl_window == nullptr) {
        std::cout << "FAILED to create GLFW window!" << std::endl;
        SContext::Terminate();
    }

    glfwSetWindowUserPointer(gl_window, window);
    glfwSetKeyCallback(gl_window, on_key_callback);
    glfwSetFramebufferSizeCallback(gl_window, on_window_resize_callback);
    glfwMakeContextCurrent(gl_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED to initialize GLAD" << std::endl;
    }

}

void SContext::PreRender() {
    glViewport(0, 0, window_->width_, window_->height_);
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SContext::PostRender() {
    glfwPollEvents();
    glfwSwapBuffers(static_cast<GLFWwindow*>(window_->GetNativeWindow()));
}

void SContext::Terminate() {
    std::cout << "Terminating Window" << std::endl;
    glfwDestroyWindow(static_cast<GLFWwindow*>(window_->GetNativeWindow()));
    glfwTerminate();
}