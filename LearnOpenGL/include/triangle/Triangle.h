#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

struct GLFWwindow;

class ITriangle
{
public:
	virtual ~ITriangle() { afterLoop(); }
	virtual void beforeLoop() = 0;
	virtual void drawTria(GLFWwindow* window) = 0;
	virtual void afterLoop() {}
};

class Triangle : public ITriangle
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
	unsigned int VBO;
	GLuint VAO;
	GLuint program;
};
#endif  // TRIANGLE_H