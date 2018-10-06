#include "tools/transform.h"
#include "transform_p.h"

namespace kite
{
   Transform::Transform()
   {
      p = new TransformImpl();
   }
   
   Transform::~Transform()
   {
      if (p)
      {
         delete p;
         p = nullptr;
      }
   }
   
   glm::mat4 Transform::GetWorldMatrix() const
   {
      return p->GetWorldMatrix();
   }
   
   void Transform::SetTranslation(const glm::vec3& translation_)
   {
      p->SetTranslation(translation_);
   }
   
   const glm::vec3& Transform::GetTranslation() const
   {
      return p->GetTranslation();
   }
   
   void Transform::SetRotation(const glm::vec3& rotation_)
   {
      p->SetRotation(rotation_);
   }
   
   const glm::vec3& Transform::GetRotation() const
   {
      return p->GetRotation();
   }
   
   void Transform::SetScaling(const glm::vec3& scaling_)
   {
      p->SetScaling(scaling_);
   }
   
   const glm::vec3& Transform::GetScaling() const
   {
      return p->GetScaling();
   }
}