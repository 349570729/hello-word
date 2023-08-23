#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const static glm::vec3 up{0.0f, 1.0f, 0.0f};
const static glm::vec3 move_front{0.0f, 0.0f, -1.0f};
const static glm::vec3 move_back{0.0f, 0.0f, 1.0f};
const static glm::vec3 move_left = glm::normalize(glm::cross(up, move_front));
const static glm::vec3 move_right = glm::normalize(glm::cross(move_front, up));
const static float speed_per_ms = 0.1f;
const static float speed_per_pixel = 0.01f;

Camera::Camera(Shader *shader)
    : shader_(shader)
{
    updateView();
}

void Camera::scroll(GLFWwindow *window, double xoffset, double yoffset)
{
    fov_ -= yoffset * 0.05;
    fov_ = std::max(fov_, 0.5f);
    fov_ = std::min(fov_, 60.0f);
    updateView();
}

void Camera::onCursorMoved(GLFWwindow *window, double xpos, double ypos)
{
    int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (GLFW_PRESS == action) {
        if (!mouse_in_dragging) {
            last_xpos_ = xpos;
            last_ypos_ = ypos;
            mouse_in_dragging = true;
        } else {
            center_ += (float)(xpos - last_xpos_) * speed_per_pixel * move_left;
            center_ += (float)(ypos - last_ypos_) * speed_per_pixel * up;
            last_xpos_ = xpos;
            last_ypos_ = ypos;
        }
        updateView();
    } else if (GLFW_RELEASE == action) {
        mouse_in_dragging = false;
    }
}

void Camera::keyAction(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if ((GLFW_PRESS == action) || (GLFW_REPEAT == action)) {
        onPressKey(key);
    }
    updateView();
}

// in the painting loop
void Camera::applyView()
{
    // shader_->use();
    if (first_draw_) {
        last_time_ = std::chrono::high_resolution_clock::now();
        first_draw_ = false;
        shader_->setMat4fv("view", 1, GL_FALSE, glm::value_ptr(view_));
        return;
    }
    auto time = std::chrono::high_resolution_clock::now();
    duration_ms_ = std::chrono::duration_cast<std::chrono::milliseconds>(time - last_time_);
    last_time_ = time;
    shader_->setMat4fv("view", 1, GL_FALSE, glm::value_ptr(view_));
}

float Camera::fov()
{
    return fov_;
}

void Camera::updateView()
{
    view_ = glm::lookAt(eye_, center_, up);
}

void Camera::onPressKey(int key)
{
    if (GLFW_KEY_W == key) {
        eye_ += speed_per_ms * duration_ms_.count() * move_front;
    } else if (GLFW_KEY_S == key) {
        eye_ += speed_per_ms * duration_ms_.count() * move_back;
    } else if (GLFW_KEY_A == key) {
        eye_ += speed_per_ms * duration_ms_.count() * move_left;
    } else if (GLFW_KEY_D == key) {
        eye_ += speed_per_ms * duration_ms_.count() * move_right;
    } else if (GLFW_KEY_H == key) {
        // reset camera
        eye_ = glm::vec3{0.0f, 4.0f, 4.0f};
        center_ = glm::vec3{0.0f, 0.0f, 0.0f};
        fov_ = 45.0f;
    }
}
