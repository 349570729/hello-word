#pragma once

#include "Triangle.h"
// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
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

