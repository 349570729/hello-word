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
	// OpenGL����ģʽҪ��ʹ��VAO
	// VAO���ס�����һЩ״̬
	// 
	// ��������buffer
	glGenBuffers(2, VBO);
	// �󶨻������
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// ������������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);

	// ����vertices�е�������ʲô���壬�����ö�������ָ��
	// 0��vertex_src����location��ֵ
	// 3����Ϊ�������Ե�������vec3��3������
	// GL_FLOAT ���������ͣ�GL_FALSE��ʾ�������ݱ�׼��
	// �������Դ�vertices[0]��ʼ��ȡ���������0
	// �����ݴ���myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ���ö�������
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]);
	// OpenGL����ģʽҪ��ʹ��VAO
	// VAO���ס�����һЩ״̬
	// 
	// �󶨻������
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// ������������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);

	// ����vertices�е�������ʲô���壬�����ö�������ָ��
	// 0��vertex_src����location��ֵ
	// 3����Ϊ�������Ե�������vec3��3������
	// GL_FLOAT ���������ͣ�GL_FALSE��ʾ�������ݱ�׼��
	// �������Դ�vertices[0]��ʼ��ȡ���������0
	// �����ݴ���myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ���ö�������
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

	// ����һ����ɫ������������ɫ�����ţ����ź���ܵ���
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

	// ����һ����ɫ������������ɫ�����ţ����ź���ܵ���
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

	// ����������ɫ��
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	// ������ɫ����Դ��,location��Ϊ�˱�����CPU��׼����������
	// ������ɫ����Ҫ�����CPU�˽�������
	const char* vertex_src = "#version 330 \n"
		"layout (location=0) in vec3 myPos; \n"
		"void main() \n"
		"{ \n"
		"	gl_Position = vec4(myPos.x, myPos.y, myPos.z, 1.0f); \n"
		"} \0";
	// ��ɫ������Դ��
	glShaderSource(vertex_shader, 1, &vertex_src, nullptr);

	// ������ɫ��
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
	// ��Ƭ��ɫ��������ͬ������ɫ��
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// Ƭ����ɫ����Ҫ����������յ���ɫ���������ȾΪ��ɫ
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
	// ��Ƭ��ɫ��������ͬ������ɫ��
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// Ƭ����ɫ����Ҫ����������յ���ɫ���������ȾΪ��ɫ
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
