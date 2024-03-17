#include "s_context.h"


// Implementation for rendering

// Callback function for keyboard input which is only called when a key is pressed, rather than 
// on each frame the key is held for - see Window::Camera::ProcessMouseMovement() for 
// implementation of a function that is key called on every frame a key is held for. 
static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto p_window = static_cast<UWindow*>(glfwGetWindowUserPointer(window));   
    p_window->HandleKeyInput(key, scancode, action, mods);
}

static void on_mouse_move_callback(GLFWwindow* window, double pos_x, double pos_y) {
    auto p_window = static_cast<UWindow*>(glfwGetWindowUserPointer(window));

    p_window->mouse_pos_x_ = static_cast<float>(pos_x);
    p_window->mouse_pos_y_ = static_cast<float>(pos_y);

    if(p_window->bMouseIn_) {
        p_window->prev_mouse_pos_x_ = p_window->mouse_pos_x_;
        p_window->prev_mouse_pos_y_ = p_window->mouse_pos_y_;
        p_window->bMouseIn_ = false;
    }
    float x_offset = p_window->mouse_pos_x_ - p_window->prev_mouse_pos_x_;
    float y_offset = p_window->prev_mouse_pos_y_ - p_window->mouse_pos_y_ ; // Inverted since up vector is (0, 1, 0)
    p_window->prev_mouse_pos_x_ = p_window->mouse_pos_x_;
    p_window->prev_mouse_pos_y_ = p_window->mouse_pos_y_;
    p_window->camera_->ProcessMouseMovement(x_offset, y_offset);
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
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
            window_->camera_->ProcessKeyboard(FORWARD, delta_time, true);
        else 
            window_->camera_->ProcessKeyboard(FORWARD, delta_time, false);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
            window_->camera_->ProcessKeyboard(LEFT, delta_time, true);
        else 
            window_->camera_->ProcessKeyboard(LEFT, delta_time, false);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
            window_->camera_->ProcessKeyboard(BACKWARD, delta_time, true);
        else 
            window_->camera_->ProcessKeyboard(BACKWARD, delta_time, false);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
            window_->camera_->ProcessKeyboard(RIGHT, delta_time, true);
        else 
            window_->camera_->ProcessKeyboard(RIGHT, delta_time, false);
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
            window_->camera_->ProcessKeyboard(UP, delta_time, true);
        else 
            window_->camera_->ProcessKeyboard(UP, delta_time, false);
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
            window_->camera_->ProcessKeyboard(DOWN, delta_time, true);
        else 
            window_->camera_->ProcessKeyboard(DOWN, delta_time, false);
    }
}

SContext::SContext(bool bPostProcessing) : UContext() {
    bPostProcessingEnabled = bPostProcessing;
}

void SContext::Init(UWindow *window) {
    window_ = window;
    collision_handler_ = new CollisionHandler();
    scene_ = std::make_unique<Scene>(
        window_->width_, 
        window_->height_, 
        window->camera_,
        collision_handler_
    );

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
    // The following functions are glfw-specific callback functions, where the 2nd parameter
    // takes in one of our application functions and fillts its parameters with the appropriate
    // data. 
    glfwSetKeyCallback(gl_window, on_key_callback);
    glfwSetCursorPosCallback(gl_window, on_mouse_move_callback);
    glfwSetFramebufferSizeCallback(gl_window, on_window_resize_callback);
    glfwMakeContextCurrent(gl_window);
    // Locks mouse to the window screen and hides it - GLFW handles recentering the mouse, giving our
    // camera 6 degrees of freedom with no threshold. 
    glfwSetInputMode(gl_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // In order to use modern OpenGL, we need to load a library that allows us to access the pointers
    // of the OpenGL api, of which there are many to chose from, with the two most popular being GLAD
    // and GLUT. 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED to initialize GLAD" << std::endl;
    }


    glEnable(GL_DEPTH_TEST);
    // *IMPORTANT - the following must be called after glad has been loaded, since they make calls to the 
    // OpenGL api.
    fbo_shader_res_ = new SShaderResource();
    post_processing_ = new PostProcessing(window_->width_, window_->height_, fbo_shader_res_);
    scene_->Init();
}

void SContext::PreRender() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SContext::SceneRender(float delta_time) {
    scene_->Render(delta_time);
}

void SContext::PostRender() {
    glfwPollEvents();
    glfwSwapBuffers(static_cast<GLFWwindow*>(window_->GetNativeWindow()));
}

void SContext::RenderWithoutPostProcessing(float delta_time) {
    PreRender();
    SceneRender(delta_time);
    PostRender();
}

void SContext::RenderWithPostProcessing(Shader* shader, PostProcessing* post_processing, float delta_time) {
    post_processing->BeginRender();
    SceneRender(delta_time);
    post_processing->EndRender();
    post_processing->RenderQuad();
    PostRender();
}

void SContext::Render(float delta_time) {
    bPostProcessingEnabled == true ? 
        RenderWithPostProcessing(fbo_shader_ , post_processing_, delta_time) 
        : RenderWithoutPostProcessing(delta_time);
} 

void SContext::Terminate() {
    std::cout << "Terminating Window" << std::endl;
    glfwDestroyWindow(static_cast<GLFWwindow*>(window_->GetNativeWindow()));
    glfwTerminate();
}