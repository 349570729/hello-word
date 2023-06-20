#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "IShader.h"
#include <string>


class Shader
{
public:
	Shader(const std::string& vertex_file, const std::string& fragment_file);
	~Shader();
	void use();
	void setBool(const std::string& uniform, bool value);
	void setInt(const std::string& uniform, int value);
	void setFloat(const std::string& uniform, float value);
private:
	GLuint createShader(GLenum shader_type, const std::string& file);
private:
	GLuint program;
};

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
	Shader shader;
};
