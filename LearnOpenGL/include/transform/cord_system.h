#ifndef CORD_SYSTEM_H
#define CORD_SYSTEM_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"
#include <chrono>
// ʹ��glDrawArrays�����������˴�������������
class GLFWwindow;

class cord
{
public:
    ~cord();
    void beforeLoop();
    void drawTria(GLFWwindow *window);
    void setFov(float fov);

private:
    void createProgram();
    GLuint createVertexShader();
    GLuint createFragmentShader();
    void setTex();
    void applyModel1();
    void applyModel2();
    void applyProject();
    void applyView();
    glm::mat4 createCamera();
    glm::mat4 moveCameraWithTime();
    glm::mat4 moveCameraWithKeyboard();

private:
    GLuint VBO;
    GLuint VAO;
    GLuint box_texture;
    GLuint smile_texture;
    GLuint program;
    GLFWwindow *window_;
    glm::vec3 eye_{0.0f, 4.0f, 10.0f};
    glm::vec3 center_{0.0f, 0.0f, 0.0f};
    std::chrono::high_resolution_clock::time_point last_time_;
    double last_xpos_;
    double last_ypos_;
    bool first_draw_{false};
    bool first_clicked_{false};
    float fov_{45.0f};
};

#endif // CORD_SYSTEM_H