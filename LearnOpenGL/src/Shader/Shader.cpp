#include "Shader.h"

#include <math.h>

#include <fstream>
#include <iostream>
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
        std::cout << "program link fail: " << errorInfo << std::endl;
    }

    // ���ź�Ϳ����ͷ�shader��
    // glDeleteShader(vertex_shader);
    // glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    // glDeleteProgram(program);
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

void Shader::setMat4fv(const std::string& uniform, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    GLint uniform_loc = glGetUniformLocation(program, uniform.data());
    glUniformMatrix4fv(uniform_loc, count, transpose, value);
}

void Shader::setVec3fv(const std::string& uniform, GLsizei count, const GLfloat* value)
{
    GLint uniform_loc = glGetUniformLocation(program, uniform.data());
    glUniform3fv(uniform_loc, count, value);
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
        printf("compile '%s' failed: %s\n", file.c_str(), errorInfo);
        // std::cout << "shader compile failed: " << errorInfo << std::endl;
        return 0;
    }
    return shader;
}
