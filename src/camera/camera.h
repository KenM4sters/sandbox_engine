#pragma once
#include "../utils/includes.h"

/**
 * Camera Class handles everything about Camera movement and passing its data such as the View matrix
 * and camera position to all shaders so that they can be rendered in 3D and have realistic shading 
 * based on where the angle of which you are viewing objects.
*/


// Simple enum to make directions a bit more intuitive.
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

struct CameraTransformData {
    glm::mat4 view_matrix;
    glm::vec3 position;
    unsigned int scr_width, scr_height;
    float fov;
};

class Camera
{
public:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;
    float yaw_;
    float pitch_;
    float movement_speed_;
    float mouse_sensitivity_;
    float zoom_;
    bool bMouseMovementEnabled_ = true;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);
    ~Camera() {
        #ifdef SANDBOX_DEBUG 
            std::cout << "Camera is being destroyed!" << std::endl;
        #endif
    }
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, float delta_time, bool speed_up = false);
    void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true);
    void ProcessMouseScroll(float y_offset);

    static Camera& GetInstance() {
        static Camera instance;
        return instance;
    }

private:
    void UpdateCameraVectors();
};
