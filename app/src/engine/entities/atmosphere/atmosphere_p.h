#ifndef ATMOSPHERE_P_H
#define ATMOSPHERE_P_H
#include "model/model.h"

namespace kite
{
   /*
      \brief private implementation of atmosphere
   */
   class AtmosphereImpl
   {
   public:
      AtmosphereImpl();
      
      void Render();
      
   private:
      Model m_sphere;//3d model of atmosphere
   };
}

#endif//ATMOSPHERE_P_H