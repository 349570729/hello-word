#include "Triangle.h"
#include <iostream>

using namespace std;

void queryMaxVertexAttri()
{
	int maxAttri;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttri);
	cout << "max vertex attribute: " << maxAttri << endl;
}

void Triangle::beforeLoop()
{

	queryMaxVertexAttri();

	createProgram();
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// OpenGL����ģʽҪ��ʹ��VAO
	// VAO���ס�����һЩ״̬
	//
	// ��������buffer
	glGenBuffers(1, &VBO);
	// �󶨻������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ������������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����vertices�е�������ʲô���壬�����ö�������ָ��
	// 0��vertex_src����location��ֵ
	// 3����Ϊ�������Ե�������vec3��3������
	// GL_FLOAT ���������ͣ�GL_FALSE��ʾ�������ݱ�׼��
	// �������Դ�vertices[0]��ʼ��ȡ���������0
	// �����ݴ���myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	// �����ݴ���myColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Triangle::drawTria(GLFWwindow *window)
{

	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Triangle::afterLoop()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program);
}

void Triangle::createProgram()
{
	GLuint vertex_shader = createVertexShader();
	GLuint fragment_shader = createFragmentShader();

	// ����һ����ɫ������������ɫ�����ţ����ź���ܵ���
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char errorInfo[512];
		glGetProgramInfoLog(program, 512, nullptr, errorInfo);
		std::cout << "program link error: " << errorInfo << std::endl;
	}

	// ���ź�Ϳ����ͷ�shader��
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

GLuint Triangle::createVertexShader()
{

	// ����������ɫ��
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	// ������ɫ����Դ��,location��Ϊ�˱�����CPU��׼����������
	// ������ɫ����Ҫ�����CPU�˽�������
	const char *vertex_src = "#version 330 \n"
							 "layout (location=0) in vec3 myPos; \n"
							 "layout (location=1) in vec3 myColor; \n"
							 "out vec3 outColor;\n"
							 "void main() \n"
							 "{ \n"
							 "	gl_Position = vec4(myPos.x, myPos.y, myPos.z, 1.0f); \n"
							 "	outColor = vec3(myColor.x, myColor.y, myColor.z); \n"
							 "} \0";
	// ��ɫ������Դ��
	glShaderSource(vertex_shader, 1, &vertex_src, nullptr);

	// ������ɫ��
	glCompileShader(vertex_shader);
	int success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char errorInfo[512];
		glGetShaderInfoLog(vertex_shader, 512, nullptr, errorInfo);
		std::cout << "vertex shader compile failed: " << errorInfo << std::endl;
	}
	return vertex_shader;
}

GLuint Triangle::createFragmentShader()
{
	// ��Ƭ��ɫ��������ͬ������ɫ��
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// Ƭ����ɫ����Ҫ����������յ���ɫ���������ȾΪ��ɫ
	const char *fragment_src = "#version 330 core \n"
							   "in vec3 outColor \n;"
							   "out vec4 frag_color; \n"
							   "void main() { \n"
							   //"frag_color = vec4(outColor, 1.0f); \n"
							   "frag_color = vec4(outColor, 1.0f); \n"
							   "}\0";
	glShaderSource(fragment_shader, 1, &fragment_src, nullptr);
	glCompileShader(fragment_shader);
	int success;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char errorInfo[512];
		glGetShaderInfoLog(fragment_shader, 512, nullptr, errorInfo);
		std::cout << "fragment shader compile failed: " << errorInfo << std::endl;
	}
	return fragment_shader;
}
