#ifndef WATER_H
#define WATER_H
#include "entities/ifc/i3dentity.h"

namespace kite
{
   /*
      \brief Dynamic water simulation model based on FFT
   */
   class Water : public I3DEntity
   {
   public:
      Water();
      ~Water();
      
      void Render() override final;
   private:
      class WaterImpl* p;
   };
}

#endif//WATER_H