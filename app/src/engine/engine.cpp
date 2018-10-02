#include "engine/engine.h"
#include "engine_p.h"

namespace kite
{
   Engine& Engine::Instance()
   {
      static Engine inst;
      return inst;
   }
   
   Engine::Engine()
   {
      p = new EngineImpl();
   }
   
   Engine::~Engine()
   {
      if (p)
      {
         delete p;
         p = nullptr;
      }
   }
   
   bool Engine::Init()
   {
      return p->Init();
   }
   
   void Engine::AddEntity(EntityType type_)
   {
      p->AddEntity(type_);
   }
   
   void Engine::Start()
   {
      p->Start();
   }
   
   I3DEntity* Engine::GetEntity(EntityType type_) const
   {
      return p->GetEntity(type_);
   }
}