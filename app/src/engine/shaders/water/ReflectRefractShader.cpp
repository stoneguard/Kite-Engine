#include "ReflectRefractShader.h"
#include "tools/resource_manager.h"

namespace kite
{
	ReflectRefractShader& ReflectRefractShader::Instance()
	{
	   static ReflectRefractShader inst;
	   return inst;
	}
	
	ReflectRefractShader::ReflectRefractShader()
	{
	   Init();
	}
	
	void ReflectRefractShader::Init()
	{
	   AttachComputeShader(_P("/shaders/water/RefractionReflectionShader_CS.glsl"));
	   Link();
	}
}
