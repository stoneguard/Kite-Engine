#ifndef NORMAL_MAP_SHADER
#define NORMAL_MAP_SHADER
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for generating normal map
   */
   class NormalMapShader final : public BaseShader
   {
   private:
      NormalMapShader();

      NormalMapShader(NormalMapShader const&) = delete;
      NormalMapShader& operator= (NormalMapShader const&) = delete;

   public:
      static NormalMapShader& Instance();

      void Init() override final;
   };
}

#endif//NORMAL_MAP_SHADER