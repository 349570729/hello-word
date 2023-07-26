#ifndef CORD_SYSTEM_H
#define CORD_SYSTEM_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"
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

private:
    GLuint VBO;
    GLuint VAO;
    GLuint box_texture;
    GLuint smile_texture;
    GLuint program;
};

#endif // CORD_SYSTEM_H