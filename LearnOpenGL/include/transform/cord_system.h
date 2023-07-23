#ifndef CORD_SYSTEM_H
#define CORD_SYSTEM_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
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

private:
    GLuint VBO;
    GLuint VAO;
    GLuint box_texture;
    GLuint smile_texture;
    GLuint program;
};

#endif // CORD_SYSTEM_H