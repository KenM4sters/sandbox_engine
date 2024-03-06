#include "s_context.h"


// Implementation for rendering

// Callback function for keyboard input, which is only called when a key is pressed, rather than 
// on each frame the button is held for. 
static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto p_window = static_cast<UWindow*>(glfwGetWindowUserPointer(window));
    p_window->HandleKeyInput(key, scancode, action, mods);
}

static void on_window_resize_callback(GLFWwindow* window, int width, int height) {
    auto p_window = static_cast<UWindow*>(glfwGetWindowUserPointer(window));
    p_window->HandleWindowResize(width, height);
}

// Processes keyboard input for the camera - key presses here will be handled on a per-frame
// basis, meaning that if you hold the key down, the funciton will be called every frame for the duration
// of the press, which is important for our camera. 
void SContext::ProcessInput(GLFWwindow* window, float delta_time) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        scene_->camera_->ProcessKeyboard(FORWARD, delta_time);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        scene_->camera_->ProcessKeyboard(LEFT, delta_time);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        scene_->camera_->ProcessKeyboard(BACKWARD, delta_time);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        scene_->camera_->ProcessKeyboard(RIGHT, delta_time);
    }
}

void SContext::init(UWindow *window) {
    window_ = window;
    scene_ = std::make_unique<Scene>(window_->width_, window_->height_);

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
    glEnable(GL_DEPTH_TEST);

    // *IMPORTANT - must be called after glad has been loaded
    scene_->Init();
}

void SContext::PreRender() {
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SContext::SceneRender(float delta_time) {
    scene_->Render(delta_time);
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