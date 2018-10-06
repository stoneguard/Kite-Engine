#ifndef TRANSFORM_P_H
#define TRANSFORM_P_H
#include <glm/glm.hpp>

namespace kite
{
   /*
      \brief private implementation of Transform
   */
   class TransformImpl
   {
   public:
      TransformImpl() = default;

      inline void SetTranslation(const glm::vec3& translation_) { m_translation = translation_; }
      inline const glm::vec3& GetTranslation() const { return m_translation; }

      inline void SetRotation(const glm::vec3& rotation_) { m_rotation = rotation_; }
      inline const glm::vec3& GetRotation() const { return m_rotation; }

      inline void SetScaling(const glm::vec3& scaling_) { m_scaling = scaling_; }
      inline const glm::vec3& GetScaling() const { return m_scaling; }

      glm::mat4 GetWorldMatrix() const;

   private:
      TransformImpl(const TransformImpl&) = delete;
      TransformImpl& operator=(const TransformImpl&) = delete;

   private:
      glm::vec3 m_translation = { 0.0f, 0.0f, 0.0f };
      glm::vec3 m_rotation;
      glm::vec3 m_scaling = { 1.0f, 1.0f, 1.0f };
   };
}
#endif//TRANSFORM_P_H