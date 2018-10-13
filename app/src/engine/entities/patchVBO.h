#ifndef PATCH_VBO_H
#define PATCH_VBO_H
#include <vector>
#include <glm/glm.hpp>
#include "tools/transform.h"

namespace kite
{
   /*
      \brief Patch of elementary vertex mesh. Represents a basis mesh for terrain and water
   */
   class PatchVBO
   {
   public:
      PatchVBO();
      ~PatchVBO();
   
      //allocate gpu resource with \a vertices_. Patches is value for pathc primitive
      void allocate(const std::vector<glm::vec2>& vertices_, int patches);

      //allocate gpu resource with \a vertices_
      void allocate(const std::vector<glm::vec3>& vertices_);
   
      //render
      void draw() const;

      //render
      void drawPoints() const;
   
      //free gpu resource
      void release();
   private:
      unsigned    m_VBO = 0;
      unsigned    m_VAO = 0;
      unsigned    m_size = 0; //size of mesh
   };
}
#endif//PATCH_VBO_H
