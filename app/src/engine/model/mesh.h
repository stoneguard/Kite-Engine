#ifndef MESH_H
#define MESH_H
#include <string>
#include <vector>
#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include "texture/texture.h"

namespace kite
{
   //Internal 3d model representation of vertex (within node)
   struct Vertex 
   {
      glm::vec3 Position;
      glm::vec3 Normal;
      glm::vec2 TexCoords;
   };
   
   /*
      \brief Represents polygonal mesh of 3d model
   */
   class Mesh 
   {
   public:
      Mesh(const std::vector<Vertex>& vertices_, const std::vector<unsigned int>& indices_, const std::vector<Texture*>& textures_);
      ~Mesh();

      void Draw();

   private:
      //allocate gpu resources
      void allocate();

      //free gpu resources
      void release();

   private:
      //mesh data
      std::vector<Vertex>           m_vertices;
      std::vector<unsigned int>     m_indices;
      std::vector<Texture*>         m_textures;

      //render data
      unsigned m_VAO = 0;
      unsigned m_VBO = 0;
      unsigned m_EBO = 0;
   };
}

#endif//MESH_H