#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>

namespace kite
{
   /*
      \brief Transform for 3d objects at scene
   */
   class __declspec(dllexport) Transform
   {
   public:
      Transform();
      ~Transform();
   
      void SetTranslation(const glm::vec3& translation_);
      const glm::vec3& GetTranslation() const;
   
      void SetRotation(const glm::vec3& rotation_);
      const glm::vec3& GetRotation() const;
   
      void SetScaling(const glm::vec3& scaling_);
      const glm::vec3& GetScaling() const;
   
      glm::mat4 GetWorldMatrix() const;
   
   private:
      class TransformImpl* p;
   };
}
#endif//TRANSFORM_H
