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
	void onKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods);

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
	float ratio{0.2};
};

#endif // TEX_H