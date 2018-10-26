#ifndef WATER_H_P
#define WATER_H_P
#include "entities/patchVBO.h"
#include "water_cfg.h"
#include "texture/texture.h"

namespace kite
{
   class I3DEntity;
   class NormalMap;
   class FFT;
   /*
      \brief Private implementation of dynamic water model
   */
   class WaterImpl
   {
   public:
      WaterImpl(I3DEntity* parent_);
      ~WaterImpl();

      void Render();

   private:
      I3DEntity*           m_parent;            //pointer to parent object
      class BaseShader*    m_shader = nullptr;  //should be able to switch to wireframe and back
      PatchVBO             m_patch;             //patch mesh, this geometry we will wave
      WaterConfiguration   m_waterCfg;          //configuration parameters of water
      NormalMap*           m_normalMap;
      FFT*                 m_fft = nullptr;
      glm::vec4            m_clipplane;
      float                m_clip_offset;
      float                m_motion = 0.f;
      float                m_distortion = 0.f;
      Texture              m_texDudv;
      Texture              m_texCaustics;
   };
}

#endif//WATER_H_P