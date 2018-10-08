#include "shaders/base_shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GL/gl3w.h"
#include <glm/glm.hpp>

namespace kite
{
   std::string loadShaderFromSource(const char* path_)
   {
      // 1. get shader source code from file at \a path_
      std::string source;
      std::ifstream file;
      // make sure ifstream can throw exceptions
      file.exceptions(std::ifstream::badbit);
      try
      {
         file.open(path_);
         std::stringstream shaderStream;
         //read file
         shaderStream << file.rdbuf();
         file.close();
         //convert to char
         source = shaderStream.str();
      }
      catch (std::ifstream::failure e)
      {
         std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
      }

      if (source.empty())
         std::cout << "Empty source shader : \"" << std::string(path_) << "\"" << std::endl;

      return source;
   }

   BaseShader::BaseShader()
   {
      m_program = glCreateProgram();
   }

   void BaseShader::attachProgram(const char* code_, int type_)
   {
      // 2. shader build
      GLuint id;
      GLint success;
      GLchar infoLog[512];

      // vertex shader
      id = glCreateShader(type_);
      glShaderSource(id, 1, &code_, NULL);
      glCompileShader(id);
      // print any compile errors
      glGetShaderiv(id, GL_COMPILE_STATUS, &success);
      if (!success)
      {
         glGetShaderInfoLog(id, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      }

      glAttachShader(m_program, id);

      //release resource
      glDeleteShader(id);
   }

   void BaseShader::setVec3(const char* name, float v0, float v1, float v2) const
   {
      GLint objectLoc = glGetUniformLocation(m_program, name);
      glUniform3f(objectLoc, v0, v1, v2);
   }

   void BaseShader::setVec3(const char* name, const glm::vec3& value) const
   {
      glUniform3fv(glGetUniformLocation(m_program, name), 1, &value[0]);
   }

   void BaseShader::setVec2(const char* name, const glm::vec2 &value) const
   {
      glUniform2fv(glGetUniformLocation(m_program, name), 1, &value[0]);
   }

   void BaseShader::setVec4(const char* name, const glm::vec4 &value) const
   {
      glUniform4fv(glGetUniformLocation(m_program, name), 1, &value[0]);
   }

   void BaseShader::setFloat(const char* name, float value_) const
   {
      GLint objectLoc = glGetUniformLocation(m_program, name);
      glUniform1f(objectLoc, value_);
   }

   void BaseShader::setInt(const char* name, int value_) const
   {
      glUniform1i(glGetUniformLocation(m_program, name), value_);
   }

   void BaseShader::setMat4(const char* name, const glm::mat4& mat) const
   {
      glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, &mat[0][0]);
   }

   void BaseShader::Use() const
   {
      glUseProgram(m_program);
   }

   void BaseShader::AttachVertexShader(const char* path_)
   {
      std::string code = loadShaderFromSource(path_);
      const GLchar* shaderCode = code.c_str();

      attachProgram(shaderCode, GL_VERTEX_SHADER);
   }

   void BaseShader::AttachTessellationControlShader(const char* path_)
   {
      std::string code = loadShaderFromSource(path_);
      const GLchar* shaderCode = code.c_str();

      attachProgram(shaderCode, GL_TESS_CONTROL_SHADER);
   }

   void BaseShader::AttachTessellationEvaluationShader(const char* path_)
   {
      std::string code = loadShaderFromSource(path_);
      const GLchar* shaderCode = code.c_str();

      attachProgram(shaderCode, GL_TESS_EVALUATION_SHADER);
   }

   void BaseShader::AttachGeometryShader(const char * path_)
   {
      std::string code = loadShaderFromSource(path_);
      const GLchar* shaderCode = code.c_str();

      attachProgram(shaderCode, GL_GEOMETRY_SHADER);
   }

   void BaseShader::AttachFragmentShader(const char* path_)
   {
      std::string code = loadShaderFromSource(path_);
      const GLchar* shaderCode = code.c_str();

      attachProgram(shaderCode, GL_FRAGMENT_SHADER);
   }

   void BaseShader::AttachComputeShader(const char* path_)
   {
      std::string code = loadShaderFromSource(path_);
      const GLchar* shaderCode = code.c_str();

      attachProgram(shaderCode, GL_COMPUTE_SHADER);
   }

   void BaseShader::Link() const
   {
      GLint success;
      GLchar infoLog[512];

      glLinkProgram(m_program);
      //print any link errors
      glGetProgramiv(m_program, GL_LINK_STATUS, &success);
      if (!success)
      {
         glGetProgramInfoLog(m_program, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      }
   }
}