#include "./camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front_(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed_(SPEED), mouse_sensitivity_(SENSITIVITY), zoom_(ZOOM)
{
    position_ = position;
    world_up_ = up;
    yaw_ = yaw;
    pitch_ = pitch;
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front_(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed_(SPEED), mouse_sensitivity_(SENSITIVITY), zoom_(ZOOM)
{
    position_ = glm::vec3(posX, posY, posZ);
    world_up_ = glm::vec3(upX, upY, upZ);
    yaw_ = yaw;
    pitch_ = pitch;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float delta_time, bool speed_up)
{
    float velocity = movement_speed_ * delta_time;
    if(speed_up) 
        velocity *= 10;
    else 
        velocity = movement_speed_ * delta_time;
        
    if (direction == FORWARD)
        position_ += front_ * velocity;
    if (direction == BACKWARD)
        position_ -= front_ * velocity;
    if (direction == LEFT)
        position_ -= right_ * velocity;
    if (direction == RIGHT)
        position_ += right_ * velocity;
    if (direction == UP)
        position_ += up_ * velocity;
    if (direction == DOWN)
        position_ -= up_ * velocity;
}

void Camera::ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch)
{
    x_offset *= mouse_sensitivity_;
    y_offset *= mouse_sensitivity_;

    yaw_   += x_offset;
    pitch_ += y_offset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrain_pitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float y_offset)
{
    zoom_ -= (float)y_offset;
    if (zoom_ < 1.0f)
        zoom_ = 1.0f;
    if (zoom_ > 45.0f)
        zoom_ = 45.0f;
}

void Camera::UpdateCameraVectors()
{
    // calculate the new front_ vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    // also re-calculate the right_ and up_ vector
    right_ = glm::normalize(glm::cross(front_, world_up_));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up_    = glm::normalize(glm::cross(right_, front_));
}