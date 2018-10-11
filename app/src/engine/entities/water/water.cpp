#include "water.h"
#include "water_p.h"

namespace kite
{
   Water::Water()
   {
      p = new WaterImpl();
   }

   Water::~Water()
   {
      delete p;
      p = nullptr;
   }

   void Water::Render()
   {
      p->Render();
   }
}

