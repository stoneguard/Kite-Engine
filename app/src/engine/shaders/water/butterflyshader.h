#ifndef BUTTERFLY_SHADER_H
#define BUTTERFLY_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for calculating result heighmap texture with a help of butterfly method.
   */
   class ButterFlyShader final : public BaseShader
   {
   private:
      ButterFlyShader();
   
      ButterFlyShader(ButterFlyShader const&) = delete;
      ButterFlyShader& operator= (ButterFlyShader const&) = delete;
   
   public:
      static ButterFlyShader& Instance();
   
      void Init() override final;
   };
}
#endif//BUTTERFLY_SHADER_H