#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include <GLFW/glfw3.h>

#include <chrono>

#include "glm/glm.hpp"

class Camera
{
public:
    Camera(Shader *shader);
    void scroll(GLFWwindow *window, double xoffset, double yoffset);
    void onCursorMoved(GLFWwindow *window, double xpos, double ypos);
    void keyAction(GLFWwindow *window, int key, int scancode, int action, int mods);
    void applyView();
    float fov();

private:
    void updateView();
    void onPressKey(int key);

private:
    Shader *shader_;
    float fov_{45.0f};
    glm::vec3 eye_{0.0f, 4.0f, 10.0f};
    glm::vec3 center_{0.0f, 0.0f, 0.0f};
    glm::mat4 view_;
    bool first_draw_{false};
    std::chrono::high_resolution_clock::time_point last_time_;
    std::chrono::milliseconds duration_ms_;
    bool mouse_in_dragging{false};
    double last_xpos_;
    double last_ypos_;
};

#endif  // CAMERA_H