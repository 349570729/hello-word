#ifndef GLTRANSFORM_H
#define GLTRANSFORM_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
// ʹ��glDrawArrays�����������˴�������������
class GLFWwindow;

class transform
{
public:
	~transform();
	void beforeLoop();
	void drawTria(GLFWwindow *window);

private:
	void createProgram();
	GLuint createVertexShader();
	GLuint createFragmentShader();
	void setTex();
	void applyTransform();

private:
	GLuint VBO;
	GLuint VAO;
	GLuint box_texture;
	GLuint smile_texture;
	GLuint program;
};

#endif // GLTRANSFORM_H