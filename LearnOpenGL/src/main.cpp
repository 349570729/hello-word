// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#include "IShader.h"
#include "Shader.h"
#include "Triangle.h"
#include "Triangle2.h"
#include "TriangleEBO.h"
#include "TriangleExercise2.h"
#include "TriangleExercise3.h"
#include "camera.h"
#include "cord_system.h"
#include "glm_demo.h"
#include "gltransform.h"
#include "tex.h"

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
// void mousebuttonfun(GLFWwindow *window, int button, int action, int mods)
// {
//     camera->mouseAction(window, button, action, mods);
// }
void keyAction(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    camera->keyAction(window, key, scancode, action, mods);
}
GLFWwindow *initGLFW(bool multi_thread)
{
    // �������ں�������
    if (!multi_thread) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    GLFWwindow *window = glfwCreateWindow(800, 600, "hello glfw", nullptr, nullptr);
    if (nullptr == window) {
        const char *error_msg = new char[100];
        glfwGetError(&error_msg);
        std::cout << "fail to create window: " << error_msg << std::endl;
        // delete[] error_msg;
        glfwTerminate();
    } else {
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
        glfwSetScrollCallback(window, scrollCallback);
        glfwSetCursorPosCallback(window, curPosChanged);
        glfwSetKeyCallback(window, keyAction);
    }
    return window;
}

void doRender(bool multi_thread)
{
    GLFWwindow *window = initGLFW(multi_thread);

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
    std::unique_ptr<cord> obj = std::make_unique<cord>();
    camera = std::make_unique<Camera>(obj->shader());
    obj->setCamera(camera.get());
    // for texture class
    // glfwSetKeyCallback(window, Texture::onKeyPress2);
    obj->beforeLoop();
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

    if (!multi_thread) {
        glfwTerminate();
    }
    // ����ǰ��Ҫ����terminate�ͷ���Դ������initʧ����
}

void render()
{
    doRender(false);
}

void multiThreadRender()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::thread t1(doRender, true);
    std::thread t2(doRender, true);
    t1.join();
    t2.join();
    glfwTerminate();
}

namespace test {
void os();
}

int main(int argc, char *argv[])
{
    // printf("Press any key to continue...");
    // getchar();
    // test::os();
    // multiThreadRender();
    render();
    // glm_main();
    return 0;
}