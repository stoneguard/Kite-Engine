#ifndef BASE_SHADER_H
#define BASE_SHADER_H
#include <glm/glm.hpp>//TODO hide to cpp

namespace kite
{
   /*
      \brief Base class for shaders. 
   */
   class BaseShader
   {
   public:
      BaseShader();
      virtual ~BaseShader() = default;
   
      //Create shader programm from source code located at hdd
      virtual void Init() = 0;

      virtual void setVec3(const char* name, float v0, float v1, float v2) const;
      virtual void setVec3(const char* name, const glm::vec3& value) const;
      virtual void setVec2(const char* name, const glm::vec2 &value) const;
      virtual void setVec4(const char* name, const glm::vec4 &value) const;
      virtual void setFloat(const char* name, float value_) const;
      virtual void setInt(const char* name, int value_) const;
      virtual void setMat4(const char* name, const glm::mat4& mat) const;

      //make shader active
      virtual void Use() const;

      virtual void AttachVertexShader(const char* path_);
      virtual void AttachTessellationControlShader(const char* path_);
      virtual void AttachTessellationEvaluationShader(const char* path_);
      virtual void AttachGeometryShader(const char* path_);
      virtual void AttachFragmentShader(const char* path_);
      virtual void AttachComputeShader(const char* path_);

      /*
         \brief Link shader programm
         \warning link only after all shaders have been attached
      */
      virtual void Link() const;
  
   private:
      void attachProgram(const char* code_, int type_);

   private:
      //shader programm id
      unsigned m_program = 0;
   };
}
#endif//BASE_SHADER_H
