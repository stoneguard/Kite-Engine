#ifndef SHADER_STORAGE_BUFFER_H
#define SHADER_STORAGE_BUFFER_H
#include <vector>
#include <glm/glm.hpp>

namespace kite
{
   /*
      \brief Actual buffer for twiddle indicies.
   */
   class ShaderStorageBuffer
   {
      public:
         ShaderStorageBuffer();
         ~ShaderStorageBuffer();
   
         void addData(const std::vector<glm::vec2>& data);
         void addData(const std::vector<int>& data);
         void bindBufferBase(int index);
      private:
         unsigned m_ssBO = 0;
   };
}
#endif//SHADER_STORAGE_BUFFER_H