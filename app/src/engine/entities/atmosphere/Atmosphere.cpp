#include "Atmosphere.h"
#include "atmosphere_p.h"

namespace kite
{
   Atmosphere::Atmosphere()
   {
      p = new AtmosphereImpl();
   }

   Atmosphere::~Atmosphere()
   {
      delete p;
      p = nullptr;
   }

   void Atmosphere::Render()
   {
      p->Render();
   }
}




