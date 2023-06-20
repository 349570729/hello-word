#pragma once

#include "Triangle.h"
// ������ͬ�����������Σ��������ǵ�����ʹ�ò�ͬ��VAO��VBO
class TriangleExercise2 : public ITriangle
{
public:
	void beforeLoop() override;
	void drawTria(GLFWwindow* window) override;
	void afterLoop() override;
private:
	void createProgram();
	GLuint createVertexShader();
	GLuint createFragmentShader();
private:
	GLuint VBO[2];
	GLuint VAO[2];
	GLuint program;
};

