#pragma once

#include <string>

#include "glad/glad.h"

class Shader {
 public:
  Shader(const std::string& vertex_file, const std::string& fragment_file);
  ~Shader();
  void use();
  void setBool(const std::string& uniform, bool value);
  void setInt(const std::string& uniform, int value);
  void setFloat(const std::string& uniform, float value);
  void setMat4fv(const std::string& uniform, GLsizei count, GLboolean transpose,
                 const GLfloat* value);

 private:
  GLuint createShader(GLenum shader_type, const std::string& file);

 private:
  GLuint program;
};