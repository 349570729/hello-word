#ifndef LIGHT_H
#define LIGHT_H

#include "Shader.h"
#include <glad.h>

class light
{
public:
    light();
    void beforeLoop();
    void drawTria(GLFWwindow *window);
    Shader *shader();

private:
private:
    GLuint VBO;
    GLuint VAO;
    Shader shader_;
};

#endif  // LIGHT_H