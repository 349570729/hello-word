#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "IShader.h"
#include <string>
#include "Shader.h"

class ShaderTriangle : public IShader
{
public:
	ShaderTriangle();
	~ShaderTriangle();
	void beforeLoop() override;
	void drawTria(GLFWwindow* window) override;
private:
	GLuint VBO{ 0 };
	GLuint VAO{ 0 };
	Shader shader_;
};
