#ifndef TEX_H
#define TEX_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
// ʹ��glDrawArrays�����������˴�������������
class GLFWwindow;

class Texture
{
public:
	~Texture();
	void beforeLoop();
	void drawTria(GLFWwindow *window);

private:
	void createProgram();
	GLuint createVertexShader();
	GLuint createFragmentShader();
	void setTex();

private:
	GLuint VBO;
	GLuint VAO;
	GLuint box_texture;
	GLuint smile_texture;
	GLuint program;
};

#endif // TEX_H