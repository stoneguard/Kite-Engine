#ifndef REFLECT_REFRACT_SHADER_H
#define REFLECT_REFRACT_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for reflection/refraction calculation
   */
	class ReflectRefractShader final : public BaseShader
	{
	private:
	   ReflectRefractShader();
	
	   ReflectRefractShader(ReflectRefractShader const&) = delete;
	   ReflectRefractShader& operator= (ReflectRefractShader const&) = delete;
	
	public:
	   static ReflectRefractShader& Instance();
	
	   void Init() override final;
	};
}

#endif//BUTTERFLY_SHADER_H