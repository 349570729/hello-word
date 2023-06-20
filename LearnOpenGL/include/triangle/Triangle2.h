#ifndef TRIANGLE2_H
#define TRIANGLE2_H

#include "Triangle.h"

// ʹ��glDrawArrays�����������˴�������������
class GLFWwindow;

class Triangle2 : public ITriangle
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

#endif  // TRIANGLE2_H