#ifndef LIGHT_H
#define LIGHT_H

#include "Shader.h"
#include <glad.h>
#include "glfw3.h"

class Light
{
public:
    Light();
    void prepare();
    void drawTria(GLFWwindow *window);
    Shader *shader();

private:
private:
    GLuint VBO;
    GLuint VAO;
    Shader shader_;
};

#endif  // LIGHT_H