#ifndef ENGINE_H
#define ENGINE_H
#include "engine/types/objects.h"

namespace kite
{
   class EngineImpl;
   class I3DEntity;
   
   /*
      \brief Init openGL context, renders etities, load resources 
   */
   class __declspec(dllexport) Engine
   {
   public:
      Engine();
      ~Engine();
   
      Engine(Engine const&) = delete;
      Engine& operator= (Engine const&) = delete;
   
   public:
      static Engine& Instance();
   
      //initialize internal opengl context
      bool Init();
   
      //starts engine
      void Start();  
      
      //add entity by type
      void AddEntity(EntityType type_);
   
      //get entity by type
      I3DEntity* GetEntity(EntityType type_) const;
   private:
      EngineImpl* p;
   };
}
#endif//ENGINE_H