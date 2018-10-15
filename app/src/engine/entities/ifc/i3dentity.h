#ifndef ENTITY_H
#define ENTITY_H
#include "tools/transform.h"

namespace kite
{
   /*
      \brief Base interface class for rendered entities
   */
   class I3DEntity
   {
   public:
      virtual ~I3DEntity() = default;
      
      //
      virtual void Render() = 0;

      virtual void SetWorldTransform(const Transform& transform_) { m_world = transform_; }
      virtual const Transform& GetWorldTransform() const { return m_world; }
      virtual Transform& GetWorldTransform() { return m_world; }
   private:
      Transform m_world;//world transform
   };
}

#endif//ENTITY_H
