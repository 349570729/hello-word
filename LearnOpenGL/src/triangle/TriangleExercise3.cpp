#include "TriangleExercise3.h"

#include <iostream>

void TriangleExercise3::beforeLoop()
{

	createProgram();
	float vertices[] = {
	-1.0f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	1.0f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	};

	glGenVertexArrays(2, VAO);
	glBindVertexArray(VAO[0]);
	// OpenGL核心模式要求使用VAO
	// VAO会记住下面的一些状态
	// 
	// 创建缓存buffer
	glGenBuffers(2, VBO);
	// 绑定缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// 拷贝缓存数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);

	// 解释vertices中的数据是什么含义，即设置顶点属性指针
	// 0是vertex_src里面location的值
	// 3是因为顶点属性的数量，vec3有3个属性
	// GL_FLOAT 是数据类型，GL_FALSE表示不做数据标准化
	// 顶点属性从vertices[0]开始读取，所以最后传0
	// 把数据传给myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 启用顶点属性
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]);
	// OpenGL核心模式要求使用VAO
	// VAO会记住下面的一些状态
	// 
	// 绑定缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// 拷贝缓存数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);

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

void TriangleExercise3::drawTria(GLFWwindow* window)
{

	glUseProgram(red_program);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(yellow_program);
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleExercise3::afterLoop()
{
	glDeleteBuffers(2, VBO);
	glDeleteVertexArrays(2, VAO);
	glDeleteProgram(red_program);
	glDeleteProgram(yellow_program);
}

void TriangleExercise3::createProgram()
{
	GLuint vertex_shader = createVertexShader();
	GLuint red_shader = createRedFragmentShader();

	// 创建一个着色器程序供上面着色器附着，附着后才能调用
	red_program = glCreateProgram();
	glAttachShader(red_program, vertex_shader);
	glAttachShader(red_program, red_shader);
	glLinkProgram(red_program);
	int success;
	glGetProgramiv(red_program, GL_LINK_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetProgramInfoLog(red_program, 512, nullptr, errorInfo);
		std::cout << "program link error: " << errorInfo << std::endl;
	}

	GLuint yellow_shader = createYellowFragmentShader();

	// 创建一个着色器程序供上面着色器附着，附着后才能调用
	yellow_program = glCreateProgram();
	glAttachShader(yellow_program, vertex_shader);
	glAttachShader(yellow_program, yellow_shader);
	glLinkProgram(yellow_program);
	glGetProgramiv(yellow_program, GL_LINK_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetProgramInfoLog(yellow_program, 512, nullptr, errorInfo);
		std::cout << "program link error: " << errorInfo << std::endl;
	}

}

GLuint TriangleExercise3::createVertexShader()
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

GLuint TriangleExercise3::createRedFragmentShader()
{
	// 碎片着色器，步骤同顶点着色器
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// 片段着色器需要负责输出最终的颜色，否则会渲染为黑色
	const char* fragment_src = "#version 330 core \n"
		"in vec3 outColor \n;"
		"out vec4 frag_color; \n"
		"void main() { \n"
		//"frag_color = vec4(outColor, 1.0f); \n"
		"frag_color = vec4(1.0f, 0.0f, 0.0f, 1.0f); \n"
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

GLuint TriangleExercise3::createYellowFragmentShader()
{
	// 碎片着色器，步骤同顶点着色器
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// 片段着色器需要负责输出最终的颜色，否则会渲染为黑色
	const char* fragment_src = "#version 330 core \n"
		"in vec3 outColor \n;"
		"out vec4 frag_color; \n"
		"void main() { \n"
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
	return GLuint();
}
