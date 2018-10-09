#ifndef SCATTERING_SHADER_H
#define SCATTERING_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Light scattering shader for simulation atmospheric effects.
   */
   class ScatteringShader final : public BaseShader
   {
   private:
      ScatteringShader();
   
      ScatteringShader(ScatteringShader const&) = delete;
      ScatteringShader& operator= (ScatteringShader const&) = delete;
   
   public:
      static ScatteringShader& Instance();
   
      void Init() override final;
   };
}
#endif//SCATTERING_SHADER_H
