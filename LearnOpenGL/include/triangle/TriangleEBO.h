#pragma once
#include "Triangle.h"
class TriangleEBO:
    public ITriangle
{
	void beforeLoop() override;
	void drawTria(GLFWwindow* window) override;
	void afterLoop() override; 
private:
	void createProgram();
	GLuint createVertexShader();
	GLuint createFragmentShader();
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	GLuint program;
};

