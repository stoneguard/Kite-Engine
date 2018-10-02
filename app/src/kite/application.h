#ifndef APPLICATION_H
#define APPLICATION_H
#include "engine/types/objects.h"

namespace kite
{
   class Engine;

   /*
      \brief Access point to engine
   */
   class Application
   {
   public:
      Application();
   
      //init app and engine within
      bool Init();

      //
      void Launch();

      //
      void AddObject(EntityType type_);

   private:
      Engine* m_engine;
   };
}
#endif//APPLICATION_H