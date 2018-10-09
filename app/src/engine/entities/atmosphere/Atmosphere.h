#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include "entities/ifc/i3dentity.h"

namespace kite
{
   /*
      \brief Representation of earth atmosphere with light scattering
   */
   class Atmosphere : public I3DEntity
   {
   public:
      Atmosphere();
      ~Atmosphere();

      void Render() override final;
      
   private:
      class AtmosphereImpl* p;
   };
}
#endif//ATMOSPHERE_H