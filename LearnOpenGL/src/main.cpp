#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "Triangle.h"
#include "TriangleEBO.h"
#include "Triangle2.h"
#include "TriangleExercise2.h"
#include "TriangleExercise3.h"
#include "IShader.h"
#include "Shader.h"
#include "tex.h"
#include <functional>

void sizeAdj(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow *initGLFW(bool multi_thread)
{
	// �������ں�������
	if (!multi_thread)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	GLFWwindow *window = glfwCreateWindow(800, 600, "hello glfw", nullptr, nullptr);
	if (nullptr == window)
	{
		const char *error_msg = new char[100];
		glfwGetError(&error_msg);
		std::cout << "fail to create window: " << error_msg << std::endl;
		delete[] error_msg;
		glfwTerminate();
	}
	else
	{
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
	}
	return window;
}

void doRender(bool multi_thread)
{
	GLFWwindow *window = initGLFW(multi_thread);

	// ����opengl�ĺ���ǰ�����ʼ��glad�����ڻ�ȡopengl������ַ
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "fail to initialize glad" << std::endl;
		return;
	}
	// ���ô����ӽ�
	glViewport(0, 0, 800, 600);
	std::cout << "init success��" << std::endl;
	// ע�ᴰ�ڳߴ�ı�ʱ�Ļص���������ʱӦ����Ӧ�����ӽ�
	glfwSetFramebufferSizeCallback(window, sizeAdj);
	auto *obj = new Texture();
	using namespace std::placeholders;
	// glfwSetKeyCallback(window, std::bind(&Texture::onKeyPress, obj, _1, _2, _3, _4));
	glfwSetKeyCallback(window, Texture::onKeyPress);
	obj->beforeLoop();
	while (!glfwWindowShouldClose(window))
	{
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, true);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		obj->drawTria(window);
	}
	delete obj;
	if (!multi_thread)
	{
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

namespace test
{
	void os();
}
int main(int argc, char *argv[])
{
	// test::os();
	// multiThreadRender();
	render();
	return 0;
}