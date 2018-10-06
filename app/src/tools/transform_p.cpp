#include "transform_p.h"
#include <glm/gtc/matrix_transform.hpp>

namespace kite
{
   glm::mat4 TransformImpl::GetWorldMatrix() const
   {
      glm::mat4 mat;
      mat = glm::translate(mat, m_translation);
   
      mat = glm::scale(mat, m_scaling);
   
      return mat;
   }
}