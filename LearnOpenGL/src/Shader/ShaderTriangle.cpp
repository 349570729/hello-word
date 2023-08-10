#include "ShaderTriangle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

const std::string uniform = "time_value";
const std::string offset = "offset";

ShaderTriangle::ShaderTriangle()
	: shader_("C:\\work\\code\\LearnOpenGL\\x64\\Debug\\vertex_shader.txt", "C:\\work\\code\\LearnOpenGL\\x64\\Debug\\fragment_shader.txt")
{
}

ShaderTriangle::~ShaderTriangle()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void ShaderTriangle::beforeLoop()
{
	float vertices[] = {
-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	// �����ݴ���myColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void ShaderTriangle::drawTria(GLFWwindow* window)
{
	shader_.use();
	glBindVertexArray(VAO);
	double time = glfwGetTime();
	float color = sin(time) / 2 + 0.5;
	shader_.setFloat(uniform, color);
	shader_.setFloat(offset, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
