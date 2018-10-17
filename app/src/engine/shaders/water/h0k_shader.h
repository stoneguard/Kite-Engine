#ifndef H0K_SHADER_H
#define H0K_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for evaluating initial equation H0(K) + H0(-K). The result will be used at time depended equation Ht(K)
   */
   class H0KShader final : public BaseShader
   {
   private:
      H0KShader();
   
      H0KShader(H0KShader const&) = delete;
      H0KShader& operator= (H0KShader const&) = delete;
   
   public:
      static H0KShader& Instance();
   
      void Init() override final;
   };
}
#endif//H0K_SHADER_H