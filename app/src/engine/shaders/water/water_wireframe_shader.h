#ifndef WATER_WIREFRAME_SHADER_H
#define WATER_WIREFRAME_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   class WaterWireFrameShader final : public BaseShader
   {
   private:
      WaterWireFrameShader();
   
      WaterWireFrameShader(WaterWireFrameShader const&) = delete;
      WaterWireFrameShader& operator= (WaterWireFrameShader const&) = delete;
   
   public:
      static WaterWireFrameShader& Instance();
   
      void Init() override final;
   };
}

#endif//WATER_WIREFRAME_SHADER_H