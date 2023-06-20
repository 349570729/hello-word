#pragma once
#include "Triangle.h"

// ����������ɫ�����򣬵ڶ�������ʹ��һ����ͬ��Ƭ����ɫ���������ɫ���ٴλ��������������Σ�������һ�����Ϊ��ɫ

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

