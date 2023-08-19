#ifndef CORD_SYSTEM_H
#define CORD_SYSTEM_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
// ʹ��glDrawArrays�����������˴�������������
class GLFWwindow;
class Camera;

class cord
{
public:
    cord();
    ~cord();
    void beforeLoop();
    void drawTria(GLFWwindow *window);
    Shader *shader();
    void setCamera(Camera *camera);

private:
    // void createProgram();
    GLuint createVertexShader();
    GLuint createFragmentShader();
    void setTex();
    void applyModel1();
    void applyModel2();
    void applyProject();
    void applyView();
    glm::mat4 createCamera();
    glm::mat4 moveCameraWithTime();

private:
    GLuint VBO;
    GLuint VAO;
    GLuint box_texture;
    GLuint smile_texture;
    // GLuint program;
    GLFWwindow *window_;
    Shader shader_;
    Camera *camera_;
};

#endif  // CORD_SYSTEM_H