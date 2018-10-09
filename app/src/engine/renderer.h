#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H
#include <vector>

namespace kite
{
   class I3DEntity;
   
   /*
      \brief Renders entities
   */
   class Renderer
   {
   public:
      Renderer() = default;
      ~Renderer();

      //add new entity
      void AddEntity(I3DEntity* entity_);
   
      //render entities
      void Render();
   private:
      std::vector<I3DEntity*> m_entities;
   };
}

#endif//RENDER_ENGINE_H
