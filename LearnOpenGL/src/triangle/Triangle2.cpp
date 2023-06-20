#include "triangle2.h"
#include <iostream>
#include <cstringt.h>

void Triangle2::beforeLoop()
{

	createProgram();
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// OpenGL核心模式要求使用VAO
	// VAO会记住下面的一些状态
	// 
	// 创建缓存buffer
	glGenBuffers(1, &VBO);
	// 绑定缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 拷贝缓存数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 解释vertices中的数据是什么含义，即设置顶点属性指针
	// 0是vertex_src里面location的值
	// 3是因为顶点属性的数量，vec3有3个属性
	// GL_FLOAT 是数据类型，GL_FALSE表示不做数据标准化
	// 顶点属性从vertices[0]开始读取，所以最后传0
	// 把数据传给myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 启用顶点属性
	glEnableVertexAttribArray(0);
}

void Triangle2::drawTria(GLFWwindow* window)
{

	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// 这样也可以画，其中每一个三角形都有一个id，可以被vertex shader访问到（gl_InstanceID）
	//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2);
}

void Triangle2::afterLoop()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program);
}

void Triangle2::createProgram()
{
	GLuint vertex_shader = createVertexShader();
	GLuint fragment_shader = createFragmentShader();

	// 创建一个着色器程序供上面着色器附着，附着后才能调用
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetProgramInfoLog(program, 512, nullptr, errorInfo);
		std::cout << "program link error: " << errorInfo << std::endl;
	}

	// 附着后就可以释放shader了
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

GLuint Triangle2::createVertexShader()
{

	// 创建顶点着色器
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	// 顶点着色器的源码,location是为了便于在CPU端准备输入数据
	// 顶点着色器需要负责从CPU端接受输入
	const char* vertex_src = "#version 330 \n"
		"layout (location=0) in vec3 myPos; \n"
		"void main() \n"
		"{ \n"
		"	gl_Position = vec4(myPos.x, myPos.y, myPos.z, 1.0f); \n"
		"} \0";
	// 着色器附加源码
	glShaderSource(vertex_shader, 1, &vertex_src, nullptr);

	// 编译着色器
	glCompileShader(vertex_shader);
	int success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetShaderInfoLog(vertex_shader, 512, nullptr, errorInfo);
		std::cout << "vertex shader compile failed: " << errorInfo << std::endl;
	}
	return vertex_shader;
}

GLuint Triangle2::createFragmentShader()
{
	// 碎片着色器，步骤同顶点着色器
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// 片段着色器需要负责输出最终的颜色，否则会渲染为黑色
	const char* fragment_src = "#version 330 core \n"
		"in vec3 outColor \n;"
		"out vec4 frag_color; \n"
		"void main() { \n"
		//"frag_color = vec4(outColor, 1.0f); \n"
		"frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f); \n"
		"}\0";
	glShaderSource(fragment_shader, 1, &fragment_src, nullptr);
	glCompileShader(fragment_shader);
	int success;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetShaderInfoLog(fragment_shader, 512, nullptr, errorInfo);
		std::cout << "fragment shader compile failed: " << errorInfo << std::endl;
	}
	return fragment_shader;
}
