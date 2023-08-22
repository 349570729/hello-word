// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>
#include "camera.h"
#include "light.h"

namespace light {
std::unique_ptr<Camera> camera;
void sizeAdj(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera->scroll(window, xoffset, yoffset);
}
void curPosChanged(GLFWwindow *window, double xpos, double ypos)
{
    camera->onCursorMoved(window, xpos, ypos);
}

void keyAction(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    camera->keyAction(window, key, scancode, action, mods);
}

GLFWwindow *initGLFW()
{
    // �������ں�������
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "hello glfw", nullptr, nullptr);
    if (nullptr == window) {
        const char *error_msg = new char[100];
        glfwGetError(&error_msg);
        std::cout << "fail to create window: " << error_msg << std::endl;
        // delete[] error_msg;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorPosCallback(window, curPosChanged);
    glfwSetKeyCallback(window, keyAction);
    return window;
}

void doRender()
{
    GLFWwindow *window = initGLFW();

    // ����opengl�ĺ���ǰ�����ʼ��glad�����ڻ�ȡopengl������ַ
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
        std::cout << "fail to initialize glad" << std::endl;
        return;
    }
    // ���ô����ӽ�
    glViewport(0, 0, 800, 600);
    std::cout << "init success��" << std::endl;
    // ע�ᴰ�ڳߴ�ı�ʱ�Ļص���������ʱӦ����Ӧ�����ӽ�
    glfwSetFramebufferSizeCallback(window, sizeAdj);
    std::unique_ptr<Light> obj = std::make_unique<Light>();
    camera = std::make_unique<Camera>(obj->shader());
    obj->prepare();
    while (!glfwWindowShouldClose(window)) {
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera->applyView();
        obj->drawTria(window);
    }
    glfwTerminate();
}

int main(int argc, char *argv[])
{
    doRender();
    return 0;
}
}  // namespace light