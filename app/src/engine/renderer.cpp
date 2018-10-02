#include "renderer.h"
#include "entities/ifc/i3dentity.h"

namespace kite
{
   void Renderer::AddEntity(I3DEntity * entity_)
   {
      m_entities.emplace_back(entity_);
   }
   
   void Renderer::Render()
   {
      for (I3DEntity* entity : m_entities)
         entity->Render();
   }
}