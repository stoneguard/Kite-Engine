#include "shader_storage_buffer.h"
#include <GL/gl3w.h>

namespace kite
{
   ShaderStorageBuffer::ShaderStorageBuffer()
   {
      glGenBuffers(1, &m_ssBO);
   }
   
   ShaderStorageBuffer::~ShaderStorageBuffer()
   {
   
   }
   
   void ShaderStorageBuffer::addData(const std::vector<glm::vec2>& data)
   {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssBO);
      glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_READ);
   }
   
   void ShaderStorageBuffer::addData(const std::vector<int>& data)
   {
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssBO);
      glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_READ);
   }
   
   void ShaderStorageBuffer::bindBufferBase(int index)
   {
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_ssBO);
   }
}