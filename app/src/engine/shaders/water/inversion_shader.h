#ifndef INVERSION_SHADER_H
#define INVERSION_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for calculating inverted bit order texture
   */
   class InversionShader final : public BaseShader
   {
   private:
      InversionShader();
   
      InversionShader(InversionShader const&) = delete;
      InversionShader& operator= (InversionShader const&) = delete;
   
   public:
      static InversionShader& Instance();
   
      void Init() override final;
   };
}
#endif//INVERSION_SHADER_H