#pragma once
#include "Triangle.h"

// 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色

class TriangleExercise3 :
    public ITriangle
{
public:
	void beforeLoop() override;
	void drawTria(GLFWwindow* window) override;
	void afterLoop() override;
private:
	void createProgram();
	GLuint createVertexShader();
	GLuint createRedFragmentShader();
	GLuint createYellowFragmentShader();
private:
	GLuint VBO[2];
	GLuint VAO[2];
	GLuint yellow_program;
	GLuint red_program;
};

