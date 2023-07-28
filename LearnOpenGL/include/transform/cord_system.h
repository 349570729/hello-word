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

private:
    void createProgram();
    GLuint createVertexShader();
    GLuint createFragmentShader();
    void setTex();
    void applyTransform1();
    void applyTransform2();
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
    std::chrono::high_resolution_clock::time_point last_time_;
};

#endif // CORD_SYSTEM_H