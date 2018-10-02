#include "application.h"
#include "engine/engine.h"

namespace kite
{
   Application::Application() 
   {
      m_engine = &Engine::Instance();
   }
   
   bool Application::Init()
   {
      return m_engine->Init();
   }
   
   void Application::Launch()
   {
      m_engine->Start();
   }
   
   void Application::AddObject(EntityType type_)
   {
      m_engine->AddEntity(type_);
   }
}