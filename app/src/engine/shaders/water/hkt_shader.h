#ifndef HKT_SHADER_H
#define HKT_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for evaluating time depended equation Ht(K)
   */
   class HktShader final : public BaseShader
   {
   private:
      HktShader();

      HktShader(HktShader const&) = delete;
      HktShader& operator= (HktShader const&) = delete;

   public:
      static HktShader& Instance();

      void Init() override final;
   };
}
#endif//HKT_SHADER_H