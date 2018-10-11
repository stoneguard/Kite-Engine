#ifndef WATER_SHADER_H
#define WATER_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Dynamic water simulation shader
   */
   class WaterShader final : public BaseShader
   {
   private:
      WaterShader();
   
      WaterShader(WaterShader const&) = delete;
      WaterShader& operator= (WaterShader const&) = delete;
   
   public:
      static WaterShader& Instance();
   
      void Init() override final;
   };
}
#endif//WATER_SHADER_H