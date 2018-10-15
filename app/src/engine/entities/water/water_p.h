#ifndef WATER_H_P
#define WATER_H_P
#include "entities/patchVBO.h"
#include "water_cfg.h"

namespace kite
{
   class I3DEntity;
   /*
      \brief Private implementation of dynamic water model
   */
   class WaterImpl
   {
   public:
      WaterImpl(I3DEntity* parent_);

      void Render();
   private:
      I3DEntity*           m_parent;            //pointer to parent object
      class BaseShader*    m_shader = nullptr;  //should be able to switch to wireframe and back
      PatchVBO             m_patch;             //patch mesh, this geometry we will wave
      WaterConfiguration   m_waterCfg;          //configuration parameters of water
   };
}

#endif//WATER_H_P