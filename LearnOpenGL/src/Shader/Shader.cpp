#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

const std::string uniform = "time_value";
const std::string offset = "offset";


Shader::Shader(const std::string& vertex_file, const std::string& fragment_file)
{
	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_file);
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_file);
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetProgramInfoLog(program, 512, nullptr, errorInfo);
		std::cout << "program link error: " << errorInfo << std::endl;
	}

	// 附着后就可以释放shader了
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::setBool(const std::string& uniform, bool value)
{
	GLint uniform_loc = glGetUniformLocation(program, uniform.data());
	glUniform1i(uniform_loc, (int)value);
}

void Shader::setInt(const std::string& uniform, int value)
{
	GLint uniform_loc = glGetUniformLocation(program, uniform.data());
	glUniform1i(uniform_loc, value);
}

void Shader::setFloat(const std::string& uniform, float value)
{
	GLint uniform_loc = glGetUniformLocation(program, uniform.data());
	glUniform1f(uniform_loc, value);
}

GLuint Shader::createShader(GLenum shader_type, const std::string& file)
{
	unsigned int shader = glCreateShader(shader_type);
	std::ifstream fstream;
	std::stringstream ss;
	fstream.open(file.data(), std::ifstream::in);
	ss << fstream.rdbuf();
	fstream.close();

	std::string src = ss.str();
	const char* src_data = src.data();
	glShaderSource(shader, 1, &src_data, nullptr);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorInfo[512];
		glGetShaderInfoLog(shader, 512, nullptr, errorInfo);
		std::cout << "shader compile failed: " << errorInfo << std::endl;
		return 0;
	}
	return shader;
}

// C:\\work\\code\\LearnOpenGL\\x64\\Debug\\

ShaderTriangle::ShaderTriangle()
	: shader("C:\\work\\code\\LearnOpenGL\\x64\\Debug\\vertex_shader.txt", "C:\\work\\code\\LearnOpenGL\\x64\\Debug\\fragment_shader.txt")
{
}

ShaderTriangle::~ShaderTriangle()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void ShaderTriangle::beforeLoop()
{

	float vertices[] = {
-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// OpenGL核心模式要求使用VAO
	// VAO会记住下面的一些状态
	// 
	// 创建缓存buffer
	glGenBuffers(1, &VBO);
	// 绑定缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 拷贝缓存数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 解释vertices中的数据是什么含义，即设置顶点属性指针
	// 0是vertex_src里面location的值
	// 3是因为顶点属性的数量，vec3有3个属性
	// GL_FLOAT 是数据类型，GL_FALSE表示不做数据标准化
	// 顶点属性从vertices[0]开始读取，所以最后传0
	// 把数据传给myPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// 启用顶点属性
	glEnableVertexAttribArray(0);

	// 把数据传给myColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void ShaderTriangle::drawTria(GLFWwindow* window)
{
	shader.use();
	glBindVertexArray(VAO);
	double time = glfwGetTime();
	float color = sin(time) / 2 + 0.5;
	shader.setFloat(uniform, color);
	shader.setFloat(offset, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
